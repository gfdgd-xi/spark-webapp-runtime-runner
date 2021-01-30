#!/usr/bin/env python3
##########################################################################################
# 作者：gfdgd xi
# 版本：1.0
# 感谢：感谢星火商店（Spark-Store）团队，提供了 spark-webapp-runtime 给大家使用，让我能做这个程序
# 基于 Python3 的 tkinter 构建的 spark-webapp-runtime 前端
##########################################################################################
#################
# 引入所需的库
#################
import tkinter as tk
import tkinter.filedialog
import tkinter.messagebox
import os

###################
# 程序所需事件
###################
# 读取文本文档
def readtxt(path):
    f = open(path, "r") # 设置文件对象
    str = f.read() # 获取内容
    f.close() # 关闭文本对象
    return str # 返回结果

# 写入文本文档
def write_txt(path, things):
    file = open(path, 'a+', encoding='UTF-8') # 设置文件对象
    file.write(things) # 写入文本
    file.close() # 关闭文本对象

# 获取用户桌面目录
def get_desktop_path():
    for line in open(get_home() + "/.config/user-dirs.dirs"): # 以行来读取配置文件
        desktop_index = line.find("XDG_DESKTOP_DIR=\"") # 寻找是否有对应项，有返回 0，没有返回 -1
        if desktop_index != -1: # 如果有对应项
            break # 结束循环
    if desktop_index == -1: # 如果是提前结束，值一定≠-1，如果是没有提前结束，值一定＝-1
        return -1
    else:
        get = line[17:-2] # 截取桌面目录路径
        get_index = get.find("$HOME") # 寻找是否有对应的项，需要替换内容
        if get != -1: # 如果有
            get = get.replace("$HOME", get_home()) # 则把其替换为用户目录（～）
        return get # 返回目录

def liulanico():
    path = tkinter.filedialog.askopenfilename(title="选择 spark-webapp-runtime 的图标", initialdir="~/", filetypes=[("全部文件", "*.*")])
    if path != "":
        e3_text.set(path)

def start():
    os.system("spark-webapp-runtime -u '" + e1.get() + "' -i '" + e3_text.get() + "' -t '" + e2_text.get() + "' -d '" + e4_text.get() + "'")

# 获取用户主目录
def get_home():
    return os.path.expanduser('~')

# 显示“关于这个程序”窗口
def about_this_program():
    tkinter.messagebox.showinfo(title="关于这个程序",message="一个基于 Python3 的 tkinter 制作的 spark-webapp-runtime 运行器\n版本：1.0\n适用平台：Linux")

# 显示“提示”窗口
def helps():
    tkinter.messagebox.showinfo(title="提示", message="提示：\n1、无")

# 生成 .desktop 文件在桌面
def make_desktop_on_start():
    if e5_text.get() == "":
        tkinter.messagebox.showinfo(title="提示", message="没有填写要保存的文件名")
    else:
        if os.path.exists(get_home() + "/.local/share/applications/" + e5_text.get() + ".desktop"): # 判断目录是否有该文件，如果有
            choose = tkinter.messagebox.askokcancel(title="提示",message="文件已经存在，是否覆盖？")  # 询问用户是否覆盖
            if choose: # 如要覆盖
                os.remove(get_home() + "/.local/share/applications/" + e5_text.get() + ".desktop") # 删除该文件
            else: # 如不覆盖
                return # 结束
        os.mknod(get_home() + "/.local/share/applications/" + e5_text.get() + ".desktop") # 创建文本文档
        write_txt(get_home() + "/.local/share/applications/" + e5_text.get() + ".desktop", "[Desktop Entry]\nName=" + e5_text.get() + "\nVersion=1.0\nExec=" + 'spark-webapp-runtime -u "' + e1.get() + '" -i "' + e3_text.get() + '" -t "' + e2_text.get() + '" -d "' + e4_text.get() + '"\nType=Application\nTerminal=false\nStartupNotify=true\nEncoding=UTF-8\nComment=' + e4_text.get() + "\nIcon=" + e3_text.get()) # 写入文本文档
        os.system("chmod 755 '" + get_home() + "/.local/share/applications/" + e5_text.get() + ".desktop" + "'")  # 赋予可执行权限
        tkinter.messagebox.showinfo(title="提示", message="生成完成！") # 显示完成对话框

# 生成 .desktop 文件在桌面
def make_desktop_on_desktop():
    if e5_text.get() == "":
        tkinter.messagebox.showinfo(title="提示", message="没有填写要保存的文件名")
    else:
        if os.path.exists(get_desktop_path() + "/" + e5_text.get() + ".desktop"): # 判断目录是否有该文件，如果有
            choose = tkinter.messagebox.askokcancel(title="提示",message="文件已经存在，是否覆盖？")  # 询问用户是否覆盖
            if choose: # 如要覆盖
                os.remove(get_desktop_path() + "/" + e5_text.get() + ".desktop") # 删除该文件
            else: # 如不覆盖
                return # 结束
        os.mknod(get_desktop_path() + "/" + e5_text.get() + ".desktop") # 创建文本文档
        write_txt(get_desktop_path() + "/" + e5_text.get() + ".desktop", "[Desktop Entry]\nName=" + e5_text.get() + "\nVersion=1.0\nExec=" + 'spark-webapp-runtime -u "' + e1.get() + '" -i "' + e3_text.get() + '" -t "' + e2_text.get() + '" -d "' + e4_text.get() + '"\nType=Application\nTerminal=false\nStartupNotify=true\nEncoding=UTF-8\nComment=' + e4_text.get() + "\nIcon=" + e3_text.get()) # 写入文本文档
        os.system("chmod 755 '" + get_desktop_path() + "/" + e5_text.get() + ".desktop" + "'")  # 赋予可执行权限
        tkinter.messagebox.showinfo(title="提示", message="生成完成！") # 显示完成对话框

# 生成 shell 文件在桌面
def make_desktop_on_shell():
    if e5_text.get() == "":
        tkinter.messagebox.showinfo(title="提示", message="没有填写要保存的文件名")
    else:
        if os.path.exists(get_desktop_path() + "/" + e5_text.get() + ".sh"): # 判断目录是否有该文件，如果有
            choose = tkinter.messagebox.askokcancel(title="提示",message="文件已经存在，是否覆盖？")  # 询问用户是否覆盖
            if choose: # 如要覆盖
                os.remove(get_desktop_path() + "/" + e5_text.get() + ".sh") # 删除该文件
            else: # 如不覆盖
                return # 结束
        os.mknod(get_desktop_path() + "/" + e5_text.get() + ".sh") # 创建文本文档
        write_txt(get_desktop_path() + "/" + e5_text.get() + ".sh", "#!/bin/bash\n" + "spark-webapp-runtime -u '" + e1.get() + "' -i '" + e3_text.get() + "' -t '" + e2_text.get() + "' -d '" + e4_text.get() + "'") # 写入文本文档
        os.system("chmod 777 '" + get_desktop_path() + "/" + e5_text.get() + ".sh" + "'") # 赋予可执行权限
        tkinter.messagebox.showinfo(title="提示", message="生成完成！") # 显示完成对话框

###########################
# 窗口创建
###########################
window = tk.Tk() # 创建窗口
window.title("spark-webapp-runtime 运行器") # 设置标题
# 设置变量以修改和获取值项
e1_text = tk.StringVar()
e2_text = tk.StringVar()
e3_text = tk.StringVar()
e4_text = tk.StringVar()
e5_text = tk.StringVar()
# 创建控件
label1 = tk.Label(window, text="要启动的网址（选填）")
e1 = tk.Entry(window, textvariable=e1_text, width=100)
label2 = tk.Label(window, text="spark-webapp-runtime 的标题（选填）")
e2 = tk.Entry(window, textvariable=e2_text, width=100)
label3 = tk.Label(window, text="spark-webapp-runtime 的图标路径（选填）")
e3 = tk.Entry(window, textvariable = e3_text, width = 100)
button1 = tk.Button(window, text="浏览", command=liulanico)
label4 = tk.Label(window, text="spark-webapp-runtime 描述信息（支持 html 标签）（如需使用 “'” 符号，请使用 \\ 转义）")
e4 = tk.Entry(window, textvariable=e4_text, width=100)
button2 = tk.Button(window, text="启动", command=start)
label5 = tk.Label(window, text="生成的 .desktop 或 shell 的文件名")
e5 = tk.Entry(window, textvariable=e5_text, width=100)
button3 = tk.Button(window, text="生成 Shell 脚本到桌面", command=make_desktop_on_shell)
button4 = tk.Button(window, text="生成 .desktop 文件到桌面", command=make_desktop_on_desktop)
button5 = tk.Button(window, text="生成 .desktop 文件到启动器", command=make_desktop_on_start)
menu = tk.Menu(window) # 设置菜单栏
programmenu = tk.Menu(menu,tearoff=0) # 设置“程序”菜单栏
menu.add_cascade(label="程序",menu=programmenu)
programmenu.add_command(label="退出程序",command=window.quit) # 设置“退出程序”项
help = tk.Menu(menu,tearoff=0) # 设置“帮助”菜单栏
menu.add_cascade(label="帮助",menu=help)
help.add_command(label="小提示",command=helps) # 设置“小提示”项
help.add_separator() # 设置分界线
help.add_command(label="关于这个程序",command=about_this_program) # 设置“关于这个程序”项
# 添加控件
window.config(menu=menu) # 显示菜单栏
label1.pack()
e1.pack()
label2.pack()
e2.pack()
label3.pack()
e3.pack()
button1.pack()
label4.pack()
e4.pack()
button2.pack()
label5.pack()
e5.pack()
button3.pack()
button4.pack()
button5.pack()
# 显示窗口
window.mainloop()