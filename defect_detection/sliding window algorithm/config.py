
class Config:
    """
    General configuration parent class
    """
    # # 切割成的行列数
    # cut_row_num = 4
    # cut_col_num = 4
    # mix_percent = 0.2   # 混合比例
    # ROOT_DATA_PATH = r'G:\Unity\all_data'   # 数据根目录
    # # 大图数据
    # src_images_path = r'G:\Unity\all_data\src_images'   # 原始图片路径
    # src_images_box_path = r'G:\Unity\all_data\src_images_box'   # detect 检测后标注框
    # src_images_labels_path = r'G:\Unity\all_data\src_labels'    # joint_image 融合后的 label for src_images
    # # 小图数据
    # small_images_path = r'G:\Unity\all_data\small_images'   # 切割好的小图位置
    # small_images_detected_path = r'G:\Unity\all_data\small_images_detected'  # 检测好目标的小图位置
    # small_labels_detected_path = r'G:\Unity\all_data\small_labels_detected'  # 检测好的小图label数据
    # # 训练的原图 以及 裁剪图的路径
    # # train_src_images_path = r'G:\Unity\all_data\train_src_images'   # 训练的原图
    # # train_images_path = r'G:\Unity\all_data\train_images'   # 训练的裁剪图

    '''
     本项目路径示意
     G:/Unity/all_data             数据根目录
        - small-images              裁剪好的小图片
        - small_images_detected     检测的图片结果
        - small_labels_detected     检测的label结果
        - src_images                原始图片
        - src_images_box            原始图片标注框（检测后标注观看）
        - src_labels                原始图片的标注
    '''

    # 切割成的行列数
    cut_row_num =1
    cut_col_num =10
    mix_percent = 0.5  # 混合比例
    ROOT_DATA_PATH = r'/image'  # 数据根目录
    # 大图数据
    src_images_path = r'/image/test/images'  # 原始图片路径
    src_images_box_path = r'/image/test/annotations'  # detect 检测后标注框
    src_images_labels_path = r'/joint_image'  # joint_image 融合后的 label for src_images
    # 小图数据
    small_images_path = r'/small/images'  # 切割好的小图位置
    small_images_detected_path = r'/small/detect'  # 检测好目标的小图位置
    small_labels_detected_path = r'/small/labels'  # 检测好的小图label数据
    # 训练的原图 以及 裁剪图的路径
    # train_src_images_path = r'G:\Unity\all_data\train_src_images'   # 训练的原图
    # train_images_path = r'G:\Unity\all_data\train_images'   # 训练的裁剪图