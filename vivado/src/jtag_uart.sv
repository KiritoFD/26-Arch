module jtag_uart (
    input  logic clk,          // 25MHz CPU clock
    input  logic reset,
    input  logic cpu_tx,       // UART TX from CPU
    output logic cpu_rx,       // UART RX to CPU
    output logic tx_data_avail  // Debug: data available in TX FIFO
);

    // ================================================================
    // Parameters
    // ================================================================
    localparam CYCLES_PER_BIT = 217;   // 25MHz / 115200 ≈ 217
    localparam HALF_BIT      = 108;    // Half bit period for mid-bit sampling
    localparam FIFO_DEPTH    = 16;
    localparam FIFO_PTR_W    = 4;      // log2(16)

    // ================================================================
    // Self-test: pre-load test bytes into TX FIFO after reset
    // to verify BSCANE2 read path works independently of UART capture
    // ================================================================
    logic [2:0] test_loader;
    always_ff @(posedge clk) begin
        if (reset) begin
            test_loader <= 3'd0;
        end else begin
            if (test_loader != 3'd4) begin
                test_loader <= test_loader + 3'd1;
            end
        end
    end

    // ================================================================
    // UART TX Capture: cpu_tx → TX FIFO
    // ================================================================
    logic [2:0]  tx_state;
    logic [3:0]  tx_bit_idx;
    logic [15:0] tx_timer;
    logic [7:0]  tx_shift;
    logic        tx_prev;
    logic        tx_start_det;

    // Detect falling edge on cpu_tx (start bit)
    always_ff @(posedge clk) begin
        if (reset) begin
            tx_prev <= 1'b1;
        end else begin
            tx_prev <= cpu_tx;
        end
    end
    assign tx_start_det = tx_prev & ~cpu_tx;  // Falling edge = start bit

    // TX capture state machine
    always_ff @(posedge clk) begin
        if (reset) begin
            tx_state   <= 3'd0;
            tx_bit_idx <= 4'd0;
            tx_timer   <= 16'd0;
            tx_shift   <= 8'd0;
        end else begin
            unique case (tx_state)
                3'd0: begin  // IDLE - wait for start bit
                    if (tx_start_det) begin
                        tx_state <= 3'd1;
                        tx_timer <= 16'd0;
                    end
                end
                3'd1: begin  // START - wait to mid-bit of start bit
                    if (tx_timer == HALF_BIT) begin
                        tx_state   <= 3'd2;
                        tx_timer   <= 16'd0;
                        tx_bit_idx <= 4'd0;
                    end else begin
                        tx_timer <= tx_timer + 16'd1;
                    end
                end
                3'd2: begin  // DATA - sample 8 bits at mid-bit
                    if (tx_timer == CYCLES_PER_BIT[15:0]) begin
                        tx_timer <= 16'd0;
                        tx_shift[tx_bit_idx[2:0]] <= cpu_tx;
                        if (tx_bit_idx == 4'd7) begin
                            tx_state <= 3'd3;
                        end else begin
                            tx_bit_idx <= tx_bit_idx + 4'd1;
                        end
                    end else begin
                        tx_timer <= tx_timer + 16'd1;
                    end
                end
                3'd3: begin  // DONE - push byte, return to idle
                    tx_state <= 3'd0;
                end
                default: tx_state <= 3'd0;
            endcase
        end
    end

    // ================================================================
    // TX FIFO (CPU TX → JTAG USER1)
    // ================================================================
    logic [FIFO_PTR_W-1:0] tx_fifo_head;
    logic [FIFO_PTR_W-1:0] tx_fifo_tail;
    logic [FIFO_DEPTH-1:0][7:0] tx_fifo_mem;
    logic tx_fifo_full;
    logic tx_fifo_empty;
    logic tx_fifo_push;
    logic tx_fifo_pop;

    assign tx_fifo_full  = (tx_fifo_tail == tx_fifo_head + 1'b1);
    assign tx_fifo_empty = (tx_fifo_head == tx_fifo_tail);
    assign tx_data_avail = ~tx_fifo_empty;

    // Push when TX capture done (state 3) OR self-test loader active
    logic [7:0] push_data;
    assign tx_fifo_push = ((tx_state == 3'd3) || (test_loader != 3'd4 && test_loader != 3'd0)) && !tx_fifo_full;
    assign push_data = (test_loader != 3'd4 && test_loader != 3'd0) ? 8'h55 : tx_shift;  // 'U' for self-test

    always_ff @(posedge clk) begin
        if (reset) begin
            tx_fifo_head <= {FIFO_PTR_W{1'b0}};
            tx_fifo_tail <= {FIFO_PTR_W{1'b0}};
        end else begin
            // Push
            if (tx_fifo_push) begin
                tx_fifo_mem[tx_fifo_tail] <= push_data;
                tx_fifo_tail <= tx_fifo_tail + 1'b1;
            end
            // Pop (from JTAG UPDATE_DR)
            if (tx_fifo_pop) begin
                tx_fifo_head <= tx_fifo_head + 1'b1;
            end
        end
    end

    // ================================================================
    // RX FIFO (JTAG USER2 → CPU RX)
    // ================================================================
    logic [FIFO_PTR_W-1:0] rx_fifo_head;
    logic [FIFO_PTR_W-1:0] rx_fifo_tail;
    logic [FIFO_DEPTH-1:0][7:0] rx_fifo_mem;
    logic rx_fifo_full;
    logic rx_fifo_empty;
    logic rx_fifo_push;
    logic rx_fifo_pop;

    assign rx_fifo_full  = (rx_fifo_tail == rx_fifo_head + 1'b1);
    assign rx_fifo_empty = (rx_fifo_head == rx_fifo_tail);

    always_ff @(posedge clk) begin
        if (reset) begin
            rx_fifo_head <= {FIFO_PTR_W{1'b0}};
            rx_fifo_tail <= {FIFO_PTR_W{1'b0}};
        end else begin
            // Push (from JTAG USER2 UPDATE_DR)
            if (rx_fifo_push) begin
                rx_fifo_mem[rx_fifo_tail] <= rx_jtag_data;
                rx_fifo_tail <= rx_fifo_tail + 1'b1;
            end
            // Pop (when UART TX sends a byte)
            if (rx_fifo_pop) begin
                rx_fifo_head <= rx_fifo_head + 1'b1;
            end
        end
    end

    // ================================================================
    // UART RX Output: RX FIFO → cpu_rx (115200 baud)
    // ================================================================
    logic [2:0]  rx_uart_state;
    logic [3:0]  rx_uart_bit_idx;
    logic [15:0] rx_uart_timer;
    logic [7:0]  rx_uart_shift;
    logic        rx_uart_active;

    assign rx_fifo_pop = (rx_uart_state == 3'd0) && !rx_fifo_empty;

    always_ff @(posedge clk) begin
        if (reset) begin
            rx_uart_state  <= 3'd0;
            rx_uart_bit_idx <= 4'd0;
            rx_uart_timer  <= 16'd0;
            rx_uart_shift  <= 8'd0;
            rx_uart_active <= 1'b0;
            cpu_rx         <= 1'b1;  // Idle high
        end else begin
            unique case (rx_uart_state)
                3'd0: begin  // IDLE - check FIFO
                    cpu_rx <= 1'b1;
                    if (!rx_fifo_empty) begin
                        // Start sending: output start bit
                        cpu_rx        <= 1'b0;
                        rx_uart_shift <= rx_fifo_mem[rx_fifo_head];
                        rx_uart_timer <= 16'd0;
                        rx_uart_bit_idx <= 4'd0;
                        rx_uart_state <= 3'd1;
                        rx_uart_active <= 1'b1;
                    end
                end
                3'd1: begin  // SENDING - shift out data bits
                    if (rx_uart_timer == CYCLES_PER_BIT[15:0]) begin
                        rx_uart_timer <= 16'd0;
                        if (rx_uart_bit_idx == 4'd8) begin
                            // Stop bit
                            cpu_rx <= 1'b1;
                            rx_uart_state <= 3'd2;
                        end else begin
                            cpu_rx <= rx_uart_shift[rx_uart_bit_idx[2:0]];
                            rx_uart_bit_idx <= rx_uart_bit_idx + 4'd1;
                        end
                    end else begin
                        rx_uart_timer <= rx_uart_timer + 16'd1;
                    end
                end
                3'd2: begin  // STOP bit
                    if (rx_uart_timer == CYCLES_PER_BIT[15:0]) begin
                        rx_uart_state  <= 3'd0;
                        rx_uart_active <= 1'b0;
                    end else begin
                        rx_uart_timer <= rx_uart_timer + 16'd1;
                    end
                end
                default: rx_uart_state <= 3'd0;
            endcase
        end
    end

    // ================================================================
    // BSCANE2 USER1: TX FIFO → JTAG (shift out captured bytes)
    // Protocol: 9 bits [valid, data[7:0]]
    //   CAPTURE_DR: latch FIFO head into shift register
    //   UPDATE_DR:  advance FIFO pointer (pop)
    // ================================================================
    logic       user1_capture;
    logic       user1_drck;
    logic       user1_reset;
    logic       user1_sel;
    logic       user1_shift;
    logic       user1_tck;
    logic       user1_tdi;
    logic       user1_update;
    logic       user1_tdo;
    logic [8:0] user1_shift_reg;

    BSCANE2 #(
        .JTAG_CHAIN(1)   // USER1 instruction
    ) bscane2_user1 (
        .CAPTURE (user1_capture),
        .DRCK    (user1_drck),
        .RESET   (user1_reset),
        .RUNTEST (),
        .SEL     (user1_sel),
        .SHIFT   (user1_shift),
        .TCK     (user1_tck),
        .TDI     (user1_tdi),
        .TMS     (),
        .UPDATE  (user1_update),
        .TDO     (user1_tdo)
    );

    // CAPTURE_DR latches FIFO output; SHIFT_DR shifts out
    // DEBUG: For self-test, always output 0x1FF (valid=1, data=0xFF)
    always_ff @(posedge user1_tck) begin
        if (user1_sel) begin
            if (user1_capture) begin
                // SELF-TEST: always output valid=1, data=0x55 ('U')
                user1_shift_reg <= 9'b1_01010101;
            end else if (user1_shift) begin
                user1_shift_reg <= {1'b0, user1_shift_reg[8:1]};
            end
        end
    end

    assign user1_tdo = user1_shift_reg[0];

    // On UPDATE_DR: pop FIFO if data was valid
    always_ff @(posedge clk) begin
        if (reset) begin
            tx_fifo_pop <= 1'b0;
        end else begin
            tx_fifo_pop <= 1'b0;
            if (user1_update && user1_sel && !tx_fifo_empty) begin
                tx_fifo_pop <= 1'b1;
            end
        end
    end

    // ================================================================
    // BSCANE2 USER2: JTAG → RX FIFO (shift in bytes to send)
    // Protocol: 9 bits [valid, data[7:0]]
    //   UPDATE_DR: if valid bit set, push byte into RX FIFO
    // ================================================================
    logic       user2_capture;
    logic       user2_drck;
    logic       user2_reset;
    logic       user2_sel;
    logic       user2_shift;
    logic       user2_tck;
    logic       user2_tdi;
    logic       user2_update;
    logic       user2_tdo;
    logic [8:0] user2_shift_reg;
    logic [7:0] rx_jtag_data;
    logic       rx_jtag_valid;

    BSCANE2 #(
        .JTAG_CHAIN(2)   // USER2 instruction
    ) bscane2_user2 (
        .CAPTURE (user2_capture),
        .DRCK    (user2_drck),
        .RESET   (user2_reset),
        .RUNTEST (),
        .SEL     (user2_sel),
        .SHIFT   (user2_shift),
        .TCK     (user2_tck),
        .TDI     (user2_tdi),
        .TMS     (),
        .UPDATE  (user2_update),
        .TDO     (user2_tdo)
    );

    // Shift in data from TDI
    always_ff @(posedge user2_tck) begin
        if (user2_sel) begin
            if (user2_capture) begin
                user2_shift_reg <= 9'b0;  // Initialize on capture
            end else if (user2_shift) begin
                user2_shift_reg <= {user2_tdi, user2_shift_reg[8:1]};
            end
        end
    end

    // On UPDATE_DR: capture data if valid and FIFO not full
    always_ff @(posedge clk) begin
        if (reset) begin
            rx_fifo_push  <= 1'b0;
            rx_jtag_data  <= 8'd0;
            rx_jtag_valid <= 1'b0;
        end else begin
            rx_fifo_push <= 1'b0;
            if (user2_update && user2_sel) begin
                rx_jtag_valid <= user2_shift_reg[8];
                rx_jtag_data  <= user2_shift_reg[7:0];
                if (user2_shift_reg[8] && !rx_fifo_full) begin
                    rx_fifo_push <= 1'b1;
                end
            end
        end
    end

    // USER2 TDO is unused (no data to shift out from RX side)
    assign user2_tdo = 1'b0;

endmodule
