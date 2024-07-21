from PIL import Image

class LSB():
    def encode(org, msg):# LSB编码
        bmsg = ''.join(format(ord(c), '08b') for c in msg)# 将待加密信息转化为二进制串
        print("Binary message: ", bmsg)
        key = len(bmsg)
        ofs = 0# 初始隐写位的偏移量

        img = org.copy()
        width, height = img.size
        cap = width*height*3# RGB图像所能容纳的最大秘密消息比特数
        if(key + ofs > cap):
            raise IndexError('length out of range')

        scale = 64# 隐写图像块数
        width //= scale
        height //= scale

        idx = 0
        isend = False
        for x in range(width):
            if(isend):
                break
            for y in range(height):
                if(isend):
                    break
                pixel = list(img.getpixel((x, y)))# 待写入位置的原始RGB值
                for i in range(len(pixel)):
                    if(idx < ofs):
                        idx += 1
                        continue
                    pixel[i] &= 0b11111110# 消除最低比特位
                    pixel[i] |= int(bmsg[idx - ofs], 2)# 进行最低比特位隐写
                    idx += 1
                    if(idx == key + ofs):
                        isend = True
                        break
                img.putpixel((x, y), tuple(pixel))# 覆写图像
        
        return img, key, ofs
    
    def decode(lsb, key, ofs):# LSB解码, 需要知道加密时的key和ofs
        width, height = lsb.size

        bmsg = ''
        idx = 0
        isend = False

        scale = 64
        width //= scale
        height //= scale

        for x in range(width):
            if(isend):
                break
            for y in range(height):
                if(isend):
                    break
                pixel = lsb.getpixel((x,y))
                for p in pixel:
                    if(idx < ofs):
                        idx += 1
                        continue
                    bmsg += str(p & 1)# 取出最低bit位
                    idx += 1
                    if(idx == key + ofs):
                        isend = True
                        break

        print("Binary message: ", bmsg)
        msg = ''
        for i in range(0, len(bmsg), 8):
            msg += chr(int(bmsg[i:i+8], 2))# 将01字符串重构为文字信息

        return msg

msg = 'CS_LAB2: CQUWATERMASKEXP'# 加密信息

img_path = './images/'
file = 'lenna.png'

if __name__ == "__main__":
    
    print("Message: ", msg)
    org = Image.open(img_path + file)# 读取原始图像
    img, key, ofs = LSB.encode(org, msg)
    img.save(img_path + 'lsb_' + file)# 保存覆写后的图像
    
    print("Key: ",key)
    print("Offset: ", ofs)

    lsb = Image.open(img_path + 'lsb_' + file)
    output = LSB.decode(lsb, key, ofs)# 解密
    print("Message: ", output)

    