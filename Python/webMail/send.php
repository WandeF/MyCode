<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    $receiver = urldecode($_POST['receiver']);
    $title = urldecode($_POST['title']);
    $content = urldecode($_POST['content']);

    $host = '127.0.0.1';  
    $port = 9000;        

    $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
    if ($socket === false) {
        echo "Failed to create socket: " . socket_strerror(socket_last_error()) . "\n";
        exit;
    }

    // 连接到 Socket 服务器
    $result = socket_connect($socket, $host, $port);
    if ($result === false) {
        echo "Failed to connect to socket: " . socket_strerror(socket_last_error($socket)) . "\n";
        exit;
    }

    // 发送请求数据
    $request =  "POST / HTTP/1.1\r\n" .
            "Host: localhost\r\n" .
            "Connection: close\r\n" .
            "Content-Type: application/x-www-form-urlencoded\r\n" .
            "\r\n" .
            "receiver=" . $receiver . "&" .
            "title=" . $title . "&" .
            "content=" . $content . "\r\n";

    socket_write($socket, $request, strlen($request));


    // 接收响应数据
    $response = '';
    while ($buffer = socket_read($socket, 1024)) {
        $response .= $buffer;
    }

    // 关闭 Socket 连接
    socket_close($socket);

    // 打印响应数据
    echo $response;
}
?>
