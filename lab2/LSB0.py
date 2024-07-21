from PIL import Image
import os
import shutil


class LSB():
    # 加密
    def encode_image(self, img, msg):
        encoded_img = img.copy()
        width, height = img.size
        key = len(msg)
        print("该图片最大承载量为：", width*height*3)
        print("key长度为: ", key)

        if key > width * height * 3:  # 每个像素点有3维
            raise ValueError("隐藏信息长度大于图片承载量!")

        print("隐写率为：", key/(width * height * 3))

        index = 0
        for x in range(width):
            for y in range(height):
                pixel = list(img.getpixel((x, y)))  # 每个像素点的r,g,b值
                for i in range(len(pixel)):
                    if index < key:
                        pixel[i] &= 0b11111110  # 将像素的最低bit置0
                        # print(index)
                        # print(binary_msg[index])
                        pixel[i] |= int(binary_msg[index], 2)  # 将隐藏信息写入LSB
                        index += 1
                encoded_img.putpixel((x, y), tuple(pixel))
        return encoded_img

    # 解密
    def decode_image(self, img, key):
        width, height = img.size
        msg = ""
        index = 0

        for x in range(width):
            for y in range(height):
                pixel = list(img.getpixel((x, y)))
                for i in range(len(pixel)):
                    if index < key:
                        bit = pixel[i] & 0b00000001  # 提取像素的最低bit位
                        msg += str(bit)
                    index += 1
        lsb_decoded_image_file = "lsb_" + original_image_file
        print(msg)
        return msg


if __name__ == "__main__":
    # driver part :
    # deleting previous folders :
    if os.path.exists("Encoded_image/"):
        shutil.rmtree("Encoded_image/")
    if os.path.exists("Decoded_output/"):
        shutil.rmtree("Decoded_output/")

    # creating new folders :
    os.makedirs("Encoded_image/")
    os.makedirs("Decoded_output/")
    original_image_file = ""  # to make the file name global variable
    lsb_encoded_image_file = ""

    while True:
        m = input(
            "To encode press '1', to decode press '2', press any other button to close: "
        )

        if m == "1":
            os.chdir("Original_image/")
            original_image_file = input(
                "Enter the name of the file with extension : ")
            lsb_img = Image.open(original_image_file)  # 读取原始图片
            print("Description : ", lsb_img,
                  "\nMode : ", lsb_img.mode)  # 显示图片模式

            secret_msg = input("请输入待隐藏信息: ")
            print("待隐藏信息长度为: ", len(secret_msg))
            binary_msg = ''.join(format(ord(c), '08b') for c in secret_msg)
            print("二进制格式为: ", binary_msg)
            os.chdir("..")
            os.chdir("Encoded_image/")

            key = len(binary_msg)
            lsb_img_encoded = LSB().encode_image(lsb_img, binary_msg)  # 执行加密
            lsb_encoded_image_file = "lsb_" + original_image_file
            lsb_img_encoded.save(lsb_encoded_image_file)
            print("Encoded images were saved!")
            os.chdir("..")

        elif m == "2":
            os.chdir("Encoded_image/")
            lsb_img = Image.open(lsb_encoded_image_file)

            os.chdir("..")
            os.chdir("Decoded_output/")
            lsb_hidden_text_binary = LSB().decode_image(lsb_img, key)
            lsb_hidden_text = ""
            for i in range(0, len(lsb_hidden_text_binary), 8):
                char = chr(int(lsb_hidden_text_binary[i:i+8], 2))
                lsb_hidden_text += char
            file = open("lsb_hidden_text.txt", "w")  # 写入文本文件
            file.write(lsb_hidden_text)
            file.close()
            print("解密的隐藏信息已保存在文本文件中!")
            os.chdir("..")

        else:
            print("LSB加密解密程序结束!")
            break
