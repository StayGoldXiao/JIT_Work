# -*- coding: utf-8 -*-
# JIT_2313203025
# 修改说明: 在爬取古诗文时，对部分无作者的格言谚语标注为佚名，即对部分在同一父元素下，没有第二个 <a> 元素的诗句进行特殊处理

import requests
from bs4 import BeautifulSoup
import time

filename = 'poetry.txt'
url = 'https://so.gushiwen.cn/mingjus/default.aspx?page={}'
header = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36'}


def page_request(url, header):
    response = requests.get(url, header)
    # html = response.content.decode('gb2312')
    responded = response.content.decode('UTF-8')
    return responded


def page_parse(html):
    soup = BeautifulSoup(html, 'lxml')
    title = soup.find('title').get_text()
    sentences = soup.select('div.left > div.sons > div.cont')
    sentence_list = []

    for sentence in sentences:
        # 获取当前 <div> 元素下的所有 <a> 元素
        links = sentence.select('a')
        if len(links) >= 1:  # 至少存在一个 <a> 元素
            poem_text = links[0].get_text()
            if len(links) == 2:  # 存在第二个 <a> 元素
                poet_text = links[1].get_text()
            else:  # 不存在第二个 <a> 元素
                poet_text = "佚名"
            temp = poem_text + "---" + poet_text
            sentence_list.append(temp)

    return sentence_list


def write_to_file(info_list, filename):
    with open(filename, 'a', encoding='utf-8') as file:  # 仍然使用 utf-8 编码方式写入文件
        for element in info_list:
            file.write(element + '\n')


print("_____程序开始运行_____")
response1 = requests.get(url)
print("响应内容的字符集编码:", response1.encoding)

for page_num in range(1, 5):
    time.sleep(1)
    current_url = url.format(page_num)
    html = page_request(current_url, header)
    info_list = page_parse(html)
    write_to_file(info_list, filename)
print("_____程序运行完毕_____")
