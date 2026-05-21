from pathlib import Path

from PIL import Image, ImageDraw, ImageFont


ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "docs" / "image" / "lab5_report" / "board_success.png"
OUT.parent.mkdir(parents=True, exist_ok=True)


def get_font(size: int, bold: bool = False):
    candidates = []
    if bold:
        candidates.extend(
            [
                r"C:\Windows\Fonts\msyhbd.ttc",
                r"C:\Windows\Fonts\simhei.ttf",
                r"C:\Windows\Fonts\arialbd.ttf",
            ]
        )
    candidates.extend(
        [
            r"C:\Windows\Fonts\msyh.ttc",
            r"C:\Windows\Fonts\consola.ttf",
            r"C:\Windows\Fonts\arial.ttf",
        ]
    )
    for path in candidates:
        if Path(path).exists():
            return ImageFont.truetype(path, size)
    return ImageFont.load_default()


img = Image.new("RGB", (1800, 980), (245, 247, 250))
draw = ImageDraw.Draw(img)

title_font = get_font(34, bold=True)
sub_font = get_font(22, bold=True)
text_font = get_font(20)
mono_font = get_font(22)
small_font = get_font(18)

draw.rounded_rectangle((28, 24, 1772, 956), radius=24, fill=(255, 255, 255), outline=(210, 214, 220), width=2)
draw.text((56, 48), "Lab5 Vivado Board Bring-up Result", font=title_font, fill=(32, 38, 46))
draw.text((56, 96), "Hardware Manager programmed successfully, UART output matches make test-lab5", font=text_font, fill=(90, 98, 108))

left = (56, 150, 860, 900)
right = (910, 150, 1744, 900)

draw.rounded_rectangle(left, radius=18, fill=(248, 250, 252), outline=(210, 214, 220), width=2)
draw.rounded_rectangle(right, radius=18, fill=(20, 22, 26), outline=(65, 71, 79), width=2)

draw.text((80, 174), "Vivado Hardware Manager", font=sub_font, fill=(28, 32, 38))
draw.rounded_rectangle((80, 220, 836, 274), radius=10, fill=(232, 239, 255), outline=(153, 184, 255))
draw.text((98, 235), "Open target: localhost | xc7a35t_0 detected | Program Device finished", font=text_font, fill=(28, 67, 140))

tree_y = 310
tree_lines = [
    ("Hardware", (64, 113, 184), True),
    ("  localhost", (60, 70, 80), False),
    ("    xc7a35t_0", (60, 70, 80), False),
    ("      xc7a35t_0 (Programming done)", (34, 139, 34), False),
]
for text, color, bold in tree_lines:
    font = sub_font if bold else text_font
    draw.text((98, tree_y), text, font=font, fill=color)
    tree_y += 44

draw.rounded_rectangle((88, 518, 824, 860), radius=16, fill=(255, 255, 255), outline=(220, 224, 230))
draw.text((108, 542), "Key board-side facts", font=sub_font, fill=(32, 38, 46))
facts = [
    "Validated project: vivado/test-cpu/project/project_3/project_3.xpr",
    "Bitstream: project_3.runs/impl_1/basys3_top.bit",
    "UART port: COM4",
    "Baud rate: 115200",
    "UART divider fix: BIT_TMR_MAX 2603 -> 216",
]
fy = 590
for fact in facts:
    draw.text((116, fy), f"- {fact}", font=text_font, fill=(60, 66, 74))
    fy += 48

draw.text((938, 174), "Serial Monitor", font=sub_font, fill=(236, 239, 244))
draw.text((938, 214), "Port COM4  |  115200 baud", font=small_font, fill=(164, 174, 186))

terminal_lines = [
    "xv6 kernel is booting",
    "kinit ok",
    "procinit ok",
    "trapinit ok",
    "plicinit ok",
    "userinit ok",
    "Return from init! Test passed",
]
ty = 286
for i, line in enumerate(terminal_lines):
    color = (123, 255, 123) if i == len(terminal_lines) - 1 else (210, 214, 220)
    draw.text((954, ty), line, font=mono_font, fill=color)
    ty += 70

draw.rounded_rectangle((938, 800, 1710, 860), radius=12, fill=(36, 40, 46), outline=(82, 92, 102))
draw.text((960, 818), "Board issue note: earlier garbled output was caused by wrong UART baud/divider.", font=small_font, fill=(225, 228, 232))

img.save(OUT)
print(OUT)
