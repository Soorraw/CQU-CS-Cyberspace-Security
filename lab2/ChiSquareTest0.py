from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import chi2


def generate_histogram_table(image_path_origin, image_path_lsb):
    # 打开图像文件
    img_origin = Image.open(image_path_origin)
    img_lsb = Image.open(image_path_lsb)
    # 获取图像的宽度和高度
    width, height = img_origin.size

    # 初始化红、绿、蓝通道的统计列表
    Histogram_origin = [0] * 256
    Histogram_lsb = [0] * 256

    # 遍历每个像素并统计RGB值
    for y in range(8):
        for x in range(8):
            r, g, b = img_origin.getpixel((x, y))
            Histogram_origin[r] += 1
            Histogram_origin[g] += 1
            Histogram_origin[b] += 1
            r, g, b = img_lsb.getpixel((x, y))
            Histogram_lsb[r] += 1
            Histogram_lsb[g] += 1
            Histogram_lsb[b] += 1

    # 将列表转换为np数组
    Histogram_origin = np.array(Histogram_origin)
    Histogram_lsb = np.array(Histogram_lsb)

    # 绘制直方图
    i = 0
    j = 255
    plt.figure(figsize=(10, 5))
    intensity = np.arange(i, j)
    plt.bar(intensity, Histogram_origin[i:j], color='blue',
            alpha=0.8, width=0.5, label='Original Image')
    plt.bar(intensity + 0.5, Histogram_lsb[i:j], color='red',
            alpha=0.8, width=0.5, label='LSB Image')
    plt.title('RGB Histogram Comparison')
    plt.xlabel('Intensity')
    plt.ylabel('Frequency')
    plt.legend()
    plt.show()
    print(Histogram_lsb)


def lsb_prob(img_path):
    img = Image.open(img_path)
    width, height = img.size
    Histogram = [0] * 256
    for x in range(8):
        for y in range(8):
            r, g, b = img.getpixel((x, y))
            Histogram[r] += 1
            Histogram[g] += 1
            Histogram[b] += 1

    Histogram = np.array(Histogram)
    # 统计相邻两像素之间个数，因此步长为2
    hi1 = Histogram[::2]
    hi2 = Histogram[1::2]
    his = (hi1 + hi2) / 2
    rows = np.where(his >= 1)[0]  # 找出并存入his大于1的数值
    if len(rows) == 0:  # 如果his无大于1，则说明不存在隐写
        return 0
    k = len(rows)
    r = np.sum(((hi1[rows] - his[rows]) ** 2) / his[rows])  # 根据公式求隐写概率
    p = 1 - chi2.cdf(r, k - 1)  # p为隐写概率，1 - chi2.cdf(r, k - 1)为卡方分布的概率密度函数
    return p


if __name__ == "__main__":
    # 图像文件路径
    image_path_origin = "lenna.png"
    image_path_lsb = "lsb_lenna.png"

    # 生成直方图
    generate_histogram_table(image_path_origin, image_path_lsb)

    p_origin = lsb_prob(image_path_origin)
    p_lsb = lsb_prob(image_path_lsb)
    print("原图存在LSB隐写概率为: ", p_origin)
    print("LSB图片存在LSB隐写概率为: ", p_lsb)
