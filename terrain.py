from PIL import Image
import wget
import os
import shutil

if not os.path.exists('client'):
    url = 'https://launcher.mojang.com/v1/objects/c0898ec7c6a5a2eaa317770203a1554260699994/client.jar' # 1.19
    filename = wget.download(url)
    print()
    os.rename(filename, 'client.zip')
    shutil.unpack_archive('client.zip', 'client')

    for file in os.listdir('client'):
        if os.path.isfile('client/' + file) and file.endswith('.class'):
            os.remove('client/' + file)

base_path = 'client/assets/minecraft/textures/block/'

image = Image.open('assets/textures/terrain.png')
size = (256, 512)

image.putalpha(0)
image.paste((0, 0, 0, 0), (0, 0, *image.size))

if image.size != size:
    image = image.resize(size)

blocks = (
    ('grass_block_top', 'stone', 'dirt', 'grass_block_side', 'oak_planks', 'smooth_stone_slab_side', 'smooth_stone', 'bricks', 'tnt_side', 'tnt_top', 'tnt_bottom', 'cobweb', 'poppy', 'dandelion', (0, 0x2a, 255), 'oak_sapling'),
    ('cobblestone', 'bedrock', 'sand', 'gravel', 'oak_log', 'oak_log_top', 'iron_block', 'gold_block', 'diamond_block', 'emerald_block', 'redstone_block', (255, 255, 255), 'red_mushroom', 'brown_mushroom', 'spruce_sapling', (255, 255, 255)),
    ('gold_ore', 'iron_ore', 'coal_ore', 'bookshelf', 'mossy_cobblestone', 'obsidian', 'grass_block_side_overlay')
)

for row in range(len(blocks)):
    for column in range(len(blocks[row])):
        item = blocks[row][column]
        if isinstance(item, str):
            texture = Image.open(base_path + item + '.png')
            image.paste(texture, (column * 16, row * 16))
        elif isinstance(item, tuple):
            image.paste(item, (column * 16, row * 16, (column + 1) * 16, (row + 1) * 16))

# alter grass block top texture
for row in range(16):
    for column in range(16):
        rgba = image.getpixel((column, row))
        image.putpixel((column, row), (int(rgba[0] / 255 * 0x8e), int(rgba[1] / 255 * 0xb9), int(rgba[2] / 255 * 0x71), rgba[3]))

# alter grass block side texture
for row in range(32, 48):
    for column in range(16 * 6, 16 * 7):
        rgba = image.getpixel((column, row))
        if rgba[3] != 0:
            image.putpixel((column - 48, row - 32), (int(rgba[0] / 255 * 0x8e), int(rgba[1] / 255 * 0xb9), int(rgba[2] / 255 * 0x71), rgba[3]))

image.save('assets/textures/terrain.png')

image.close()
