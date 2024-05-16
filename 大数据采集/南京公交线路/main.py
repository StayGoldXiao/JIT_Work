# -*- coding: utf-8 -*-
# JIT_2313203025
import pandas as pd
import requests
from bs4 import BeautifulSoup
import time

url_filename = 'demo.csv'
info_filename = 'demo1.csv'
url = "https://nanjing.8684.cn"
url1 = "/line{}"
url_header = ['URL', '线路']
bus_header = ['线路名称', '线路类型', '运行时间', '参考票价', '公交公司', '最后更新', '公交路线-往']
# 1-5 轨道交通 江南线路(1-399) 江北线路(400-699) 江宁线路(700-999) 接驳线路(B)


header = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36"}


def page_request(url, header):  # 发起请求并返回响应内容。
    response = requests.get(url, header)
    responded = response.content.decode('UTF-8')
    return responded


def page_parse(html):  # 解析返回的响应内容，提取公交路线的链接和相关描述信息。
    bus_url = []
    soup = BeautifulSoup(html, 'lxml')
    # 查找包含公交路线链接的<a>标签
    links = soup.select('.list.clearfix a')  # 查找class为'list clearfix'的<div>元素内的所有<a>标签

    # 遍历链接并提取信息
    for link in links:
        # 提取链接的href属性（URL后缀）
        url_suffix = link.get('href')
        # 提取链接的文本内容（说明信息）
        route_description = link.get_text(strip=True)
        # 将提取的信息添加到二维列表中
        bus_url.append([url_suffix, route_description])
    return bus_url


def page_parse_sub(html):  # 解析公交路线详情页面的HTML内容，提取具体的公交路线信息。
    soup = BeautifulSoup(html, 'lxml')
    bus_info_list = []
    info_div = soup.find('div', class_='info')
    if info_div:
        # 提取线路名称和线路类型
        line_name = info_div.h1.span.get_text(strip=True)
        line_type = info_div.h1.a.get_text(strip=True) if info_div.h1.a else None
        # 提取路线
        route_line = soup.find('div', class_='bus-lzlist mb15').find_all('li')
        route_line = '---'.join([a.get_text(strip=True) for a in route_line])
        # 提取运行时间、参考票价、公交公司和最后更新
        for desc_li in info_div.find('ul', class_='bus-desc').find_all('li'):
            desc_text = desc_li.get_text(strip=True)
            if '运行时间' in desc_text:
                run_time = desc_text.split('：')[1].strip()
            elif '参考票价' in desc_text:
                reference_price = desc_text.split('：')[1].strip()
            elif '公交公司' in desc_text:
                company = desc_li.find('a').get_text(strip=True) if desc_li.find('a') else None
            elif '最后更新' in desc_text:
                last_update = desc_text.split('：')[1].strip()[0:10]

        bus_info = {# 假设所有信息都已提取，添加到列表中
            '线路名称': line_name,
            '线路类型': line_type,
            '运行时间': run_time,
            '参考票价': reference_price,
            '公交公司': company,
            '最后更新': last_update,
            '公交路线-往': route_line
        }
        bus_info_list.append(bus_info)

    return bus_info_list


print("---------------------公交路线爬取开始---------------------")
header_written = False
for page_num in range(2, 6):  # 排除地铁的页面{1}
    # time.sleep(1)
    current_url = url + url1.format(page_num)
    print(f"当前正在爬取的URL: {current_url}")
    html = page_request(current_url, header)
    info_list = page_parse(html)

    # 将数据转换为pandas DataFrame
    df = pd.DataFrame(info_list, columns=url_header)  # 假设第一行是列名，其余是数据
    # 将DataFrame保存到CSV文件
    # index=False表示不保存行索引到CSV中, header=False 排除列名

    if not header_written:
        # 如果是第一次迭代，则写入列名和数据
        df.to_csv(url_filename, index=False, encoding='utf-8', mode='w', header=True)
        # 设置标志为True，表示已写入列名
        header_written = True
    else:
        # 如果不是第一次迭代，则只追加数据
        df.to_csv(url_filename, index=False, encoding='utf-8', mode='a', header=False)

dff = pd.read_csv(url_filename)
info_list = dff.iloc[:, 0]
header_written = False

for url_info in info_list:
    current_url = url + url_info
    print(f"当前正在爬取的URL: {current_url}")
    html = page_request(current_url, header)
    bus_info_list = page_parse_sub(html)

    # 创建DataFrame
    df = pd.DataFrame(bus_info_list, columns=bus_header)

    # 判断是否已写入列名
    if not header_written:
        # 如果是第一次迭代，则写入列名和数据
        df.to_csv(info_filename, index=False, encoding='utf-8', mode='w', header=True)
        # 设置标志为True，表示已写入列名
        header_written = True
    else:
        # 如果不是第一次迭代，则只追加数据
        df.to_csv(info_filename, index=False, encoding='utf-8', mode='a', header=False)
print("---------------------公交路线爬取结束---------------------")
print("------------------请在bus_info.csv查看------------------")