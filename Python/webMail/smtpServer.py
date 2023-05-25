import datetime
import socket
import base64

smtp_server = "smtp.qq.com"
smtp_port = 25

sender = "2665233825@qq.com"
password = ""

def send_mail(smtp_socket, sender, receiver, title, content):

    #将消息整理成符合smtp格式的数据，发送出去
    data = ""
    
    #整合
    data = "From: " + sender + "\r\n"
    data += "To: " + receiver + "\r\n"
    data += "Subject: " + title + "\r\n"
    data += "Date: " + datetime.datetime.now().strftime("%a, %d %b %Y %H:%M:%S %z") + "\r\n"
    data += "\r\n"  # 空行分隔头部和正文
    data += content

    #发送sender邮箱
    smtp_socket.send(("MAIL FROM: <" + sender + ">\r\n").encode())
    recv0 = smtp_socket.recv(1024).decode()
    print("c:"+"MAIL FROM: <" + sender + ">\r\n")
    if '250' != recv0[:3]:
        print('250 reply not received from server')
    print("s:"+recv0)

    #发送receiver邮箱
    smtp_socket.send(("RCPT TO: <" + receiver + ">\r\n").encode())
    recv1 = smtp_socket.recv(1024).decode()
    print("c:"+"RCPT TO: <" + receiver + ">\r\n")
    if '250' != recv1[:3]:
        print('250 reply not received from server')
    print("s:"+recv1)

    #发送整合好的数据
    smtp_socket.send("DATA\r\n".encode())
    recv2 = smtp_socket.recv(1024).decode()
    print("c:"+"DATA\r\n")
    if '354' != recv2[:3]:
        print('354 reply not received from server')
    print("s:"+recv2)
    
    #数据以.结尾
    smtp_socket.send(data.encode() + b"\r\n.\r\n")
    recv3 = smtp_socket.recv(1024).decode()
    print("c:"+data)
    if '250' != recv3[:3]:
        print('250 reply not received from server')
    print("s:"+recv3)


def start_smtp(receiver, title, content):

    #新建一个socket对象，用于与smtp服务器之间的连接
    smtp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    smtp_socket.connect((smtp_server, smtp_port))
    recv = smtp_socket.recv(1024).decode()

    if '220' != recv[:3]:
        print('220 reply not received from server.')
    
    #发送helo信息，如果smtp服务器没问题，一定会返回允许信息
    helo = "HELO 666\r\n"
    smtp_socket.send(b"HELO 666\r\n")
    recv0 = smtp_socket.recv(1024).decode()  
    print("c:"+helo)
    print("s:"+recv0)

    #发送登录信息，准备登录，回应为334
    auth = "AUTH LOGIN\r\n"
    smtp_socket.send(b"AUTH LOGIN\r\n")
    recv1 = smtp_socket.recv(1024).decode()  
    print("c:"+auth)
    if '334' != recv1[:3]:
        print('334 reply not received from server.')
    print("s:"+recv1)

    #发送base64编码的sender邮箱，所有发送的数据都是base64编码
    smtp_socket.send(base64.b64encode(sender.encode()) + b"\r\n")
    recv2 = smtp_socket.recv(1024).decode() 
    print("c:"+sender)
    if '334' != recv2[:3]:
        print('334 reply not received from server.')
    print("s:"+recv2)

    #发送base64编码的授权码。
    smtp_socket.send(base64.b64encode(password.encode()) + b"\r\n")
    print("c:"+password)
    recv3 = smtp_socket.recv(1024).decode()
    if '235' != recv3[:3]:
        print('235 reply not received from server.')
    print("s:"+recv3)

    #发送邮件消息
    send_mail(smtp_socket, sender, receiver,  title, content)

    smtp_socket.send(b"QUIT\r\n")
    print("QUIT\r\n")
    smtp_socket.close()


def handle_request(request_data):
    #处理数据，分解出消息体
    headers_end = request_data.find('\r\n\r\n')
    headers = request_data[:headers_end].split('\r\n')
    body = request_data[headers_end + 4:]

    datas = body.split("&")
    
    receiver = ""
    title = ""
    content = ""
    #得到消息体内容
    for data in datas:
        key, value = data.split("=")
    
        if key == "receiver":
            receiver = value.strip()
        elif key == "title":
            title = value.strip()
        elif key == "content":
            content = value.split("\\")[0].strip()

    #开始连接邮件服务器
    start_smtp(receiver, title, content)

def start_server():

    #设定监听http消息的socket服务端端口
    host = '127.0.0.1'
    port = 9000
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)

    print("waiting connect...")


    client_socket, client_address = server_socket.accept()
    print("connect success!:",client_address)

    #处理请求信息
    request_data = client_socket.recv(1024).decode('utf-8')
    handle_request(request_data)

    response_data = "Send success!"
    client_socket.sendall(response_data.encode('utf-8'))


#开始程序
start_server()