from PIL import Image
from scipy.stats import chi2
import matplotlib.pyplot as plt
import numpy as np

def histogram(img_path, file):
    
    org = Image.open(img_path + file)# 读取原图和隐写图
    lsb = Image.open(img_path + 'lsb_' + file)

    width, height = org.size
    org_his = [0] * 256# 初始化灰度直方图
    lsb_his = [0] * 256

    scale = 64
    width //= scale
    height //= scale

    print("Width: ", width)
    print("Height: ", height)

    for x in range(width):
        for y in range(height):
            r, g, b = org.getpixel((x, y))# 分别统计灰度分布情况
            org_his[r] += 1
            org_his[g] += 1
            org_his[b] += 1
            r, g, b = lsb.getpixel((x, y))
            lsb_his[r] += 1
            lsb_his[g] += 1
            lsb_his[b] += 1

    l = 0
    r = 255
    plt.figure(figsize=(10, 5))# 绘制直方图
    intensity = np.arange(l, r)
    plt.bar(intensity, org_his[l:r], color = 'blue',
            alpha = 0.8, width = 0.5, label = 'Original Image')
    plt.bar(intensity + 0.5, lsb_his[l:r], color='red',
            alpha = 0.8, width = 0.5, label = 'LSB Image')
    plt.title('RGB his Comparison')
    plt.xlabel('Intensity')
    plt.ylabel('Frequency')
    plt.legend()
    plt.show()
    return org_his, lsb_his

def lsbchi(his):
    his = np.array(his)
    hi1 = his[0::2]
    hi2 = his[1::2]
    his3 = (hi1 + hi2) / 2
    rows = np.where(his3 >= 1)[0]# 分母为零时不存在隐写
    if len(rows) == 0:
        return 0
    k = len(rows)
    r = np.sum(((hi1[rows] - his3[rows]) ** 2) / his3[rows])# 隐写概率
    return chi2.cdf(r, k - 1)# 卡方统计量

img_path = './images/'
file = 'lenna.png'

if __name__ == "__main__":

    org, lsb = histogram(img_path, file)

    # print(org[0::2])
    # print(org[1::2])
    # print(lsb[0::2])
    # print(lsb[1::2])
    # print(sum(lsb[0::2]), sum(lsb[1::2]))
    print("Original: %.2f%%"%((1 - lsbchi(org))*100))# 原图的隐写概率
    print("LSB: %.2f%%"%((1 - lsbchi(lsb))*100))# 隐写图的隐写概率
    # print(org)
    # print(lsb)
    # stat, p = chisquare(lsb[0::2], lsb[1::2])
    # print("Chi-square statistic: ", stat)
    # print("P: ", p)

    # stat, p = chisquare(org[0::2], org[1::2])
    # print("Chi-square statistic: ", stat)
    # print("P: ", p)