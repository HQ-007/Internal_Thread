import os
import cv2
#from cv2 import cv2
from config import Config

mix_percent = Config.mix_percent  # 图片混合比例


def split_image(src_path, rownum, colnum, file, save_path, save_mix=True):
    # save_path+file+编号 组成保存的新文件名
    print(src_path)
    img = cv2.imread(src_path)
    # cv2.imwrite(path, img)
    size = img.shape[0:2]
    w = size[1]
    h = size[0]
    print(file, w, h)
    # 每行的高度和每列的宽度
    row_height = h // rownum
    col_width = w // colnum


    num = 0
    for i in range(rownum):
        for j in range(colnum):
            new_path = save_path
            row_start = j * col_width
            row_end = (j + 1) * col_width
            col_start = i * row_height
            col_end = (i + 1) * row_height
            # print(row_start, row_end, col_start, col_end)
            # cv2图片： [高， 宽]
            child_img = img[col_start:col_end, row_start:row_end]
            new_path = save_path + '/' + file + '_' + str(num) + '.jpg'
            cv2.imwrite(new_path, child_img)
            num += 1

    # for j in range(colnum):
    #     new_path = save_path
    #     row_start = j * col_width
    #     row_end = (j + 1) * col_width
    #     col_start = 0
    #     col_end = row_height
    #     # print(row_start, row_end, col_start, col_end)
    #     # cv2图片： [高， 宽]
    #     child_img = img[col_start:col_end, row_start:row_end]
    #     new_path = save_path + '/' + file + '_' + str(num) + '.jpg'
    #     cv2.imwrite(new_path, child_img)
    #     num += 1

    if save_mix:
        img_mix(img, row_height, col_width, save_path, file)

def img_mix(img, row_height, col_width, save_path, file):
    mix_num = 9
    # 每行的高度和每列的宽度

    # 分割成4*4就是有
    # 4*3个行融合区域
    # 3*4个列融合区域
    # 一行的融合
    row = 0
    for i in range(1):
        print(i)
        mix_height_start = i * row_height
        mix_height_end = (i + 1) * row_height
        for j in range(mix_num):
            print(j)
            mix_row_path = save_path + '/' + file + '_mix_row_' + str(row) + '.jpg'
            mix_row_start = int(j * col_width + col_width * (1 - mix_percent))
            mix_row_end = int(mix_row_start + col_width * mix_percent * 2)
            # print(mix_height_start, mix_height_end, mix_row_start, mix_row_end)
            mix_row_img = img[mix_height_start:mix_height_end, mix_row_start:mix_row_end]
            cv2.imwrite(mix_row_path, mix_row_img)
            row += 1

    #col = 0
    # 一列的融合
    # for i in range(mix_num):
    #     mix_col_start = int(i * row_height + row_height * (1 - mix_percent))
    #     mix_col_end = int(mix_col_start + row_height * mix_percent * 2)
    #     for j in range(mix_num + 1):
    #         mix_col_path = save_path + '/' + file + '_mix_col_' + str(col) + '.jpg'
    #         mix_width_start = j * col_width
    #         mix_width_end = (j + 1) * col_width
    #         # print(mix_col_start, mix_col_end, mix_width_start, mix_width_end)
    #         mix_col_img = img[mix_col_start:mix_col_end, mix_width_start:mix_width_end]
    #         cv2.imwrite(mix_col_path, mix_col_img)
    #         col += 1

# def img_mix(img, row_height, col_width, save_path, file):
#     mix_num = 3
#     # 每行的高度和每列的宽度
#
#     # 分割成4*4就是有
#     # 4*3个行融合区域
#     # 3*4个列融合区域
#     # 一行的融合
#     row = 0
#     for i in range(mix_num + 1):
#         mix_height_start = i * row_height
#         mix_height_end = (i + 1) * row_height
#         for j in range(mix_num):
#             mix_row_path = save_path + '/' + file + '_mix_row_' + str(row) + '.jpg'
#             mix_row_start = int(j * col_width + col_width * (1 - mix_percent))
#             mix_row_end = int(mix_row_start + col_width * mix_percent * 2)
#             # print(mix_height_start, mix_height_end, mix_row_start, mix_row_end)
#             mix_row_img = img[mix_height_start:mix_height_end, mix_row_start:mix_row_end]
#             cv2.imwrite(mix_row_path, mix_row_img)
#             row += 1
#
#     col = 0
#     # 一列的融合
#     for i in range(mix_num):
#         mix_col_start = int(i * row_height + row_height * (1 - mix_percent))
#         mix_col_end = int(mix_col_start + row_height * mix_percent * 2)
#         for j in range(mix_num + 1):
#             mix_col_path = save_path + '/' + file + '_mix_col_' + str(col) + '.jpg'
#             mix_width_start = j * col_width
#             mix_width_end = (j + 1) * col_width
#             # print(mix_col_start, mix_col_end, mix_width_start, mix_width_end)
#             mix_col_img = img[mix_col_start:mix_col_end, mix_width_start:mix_width_end]
#             cv2.imwrite(mix_col_path, mix_col_img)
#             col += 1


def cut_image_main(#file_path=r'/image/test/images/0000006_00159_d_0000001.jpg',
                   #save_path=r'/small/images',
                   # file_path=r'D:\航拍图片\VisDrone2019-DET-test-dev\images',
                   # save_path=r'D:\航拍图片\small',
                   # file_path=r'/home/huangqing/YOLOv5small/src_images/val/images',
                   # save_path=r'/home/huangqing/YOLOv5small/small_images/images/val',
                   file_path,
                   save_path,
                   cut_row_num, cut_col_num,
                   save_mix):
    print(f'开始切割图片, 保存 mix') if save_mix else print(f'开始切割图片, 不保存 mix')
    file_names = os.listdir(file_path)
    print(file_names)
    for file in file_names:
        print(file)
        src = file_path + '/' + file

        split_image(src, cut_row_num, cut_col_num, file.split('.')[0], save_path, save_mix)

    print(f'图片分割完成，保存在:{save_path}')

cut_image_main(  file_path=r'/home/huangqing/YOLOv5_内螺纹/YOLOv5small/src_images/images2',
                   save_path=r'/home/huangqing/YOLOv5_内螺纹/YOLOv5small/small_0.5/images2',
                   cut_row_num=1, cut_col_num=10,
                   save_mix=True

)
