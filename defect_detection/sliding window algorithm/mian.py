import config
import cut_image
import joint_image
import draw_box
import os



def is_exists(paths):
    for path in paths:
        if not os.path.exists(path):
            os.makedirs(path)
            print('创建目录：', path.split('/')[-1])
        else:
            print(path.split('/')[-1], '目录已存在')


if __name__ == '__main__':
    config = config.Config
    ROOT_data = config.ROOT_DATA_PATH
    detect_images_path = config.src_images_path
    src_labels_path = config.src_images_labels_path
    src_images_box_path = config.src_images_box_path
    small_images_path = config.small_images_path
    small_images_detected_path = config.small_images_detected_path
    small_label_save_path = config.small_labels_detected_path
    mix_percent = config.mix_percent
    cut_row_num = config.cut_row_num
    cut_col_num = config.cut_col_num

    is_exists([ROOT_data, detect_images_path, src_labels_path, src_images_box_path, small_images_path,
               small_images_detected_path, small_label_save_path])

    # 运行前处理图片
    # save_mix=False， 在检测的时候，不检测融合部分的图片（因为还没做好处理）
    cut_image.cut_image_main(detect_images_path, small_images_path, cut_row_num, cut_col_num, save_mix=False)
    '''
    # 此处为yolov5-detect.py的检测部分
    # 注意要把检测的路径改成自己的路径，  - small_images
    opt = parse_opt()
    main(opt)
    '''
    # print(detect_image_path)
    print('检测完毕, 准备融合数据...')
    joint_image.joint_main(detect_images_path, small_label_save_path, src_labels_path, mix_percent, cut_row_num, cut_col_num)
    print('融合完毕')
    # print('融合完毕, 画框...')
    # draw_box.draw_main(src_images_box_path, src_labels_path, detect_images_path)

