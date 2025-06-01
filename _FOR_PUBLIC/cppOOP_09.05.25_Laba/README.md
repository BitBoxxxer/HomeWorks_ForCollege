## Требования
C++17
## Сборка
Клонируйте репозиторий или скачайте исходники.
Установите Boost, если еще не установлено.
# Запуск
CopyRun
./server
По умолчанию сервер слушает порт 12345.

### Примеры тестовых запросов
Можно использовать curl, telnet или написать небольшой скрипт на Python.

### Через telnet или nc
CopyRun
telnet localhost 12345
После подключения вводите команды, например:

CopyRun
REGISTER:john:pass123:User
Примеры на Python (используя сокеты)
CopyRun
import socket

HOST = '127.0.0.1'
PORT = 12345

def send_command(command):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall((command + '\n').encode())
        response = s.recv(1024).decode()
        print('Response:', response)

# Регистрация нового пользователя
send_command('REGISTER:john:pass123:User')

# Вход в систему
send_command('LOGIN:john:pass123')

# Получение ресурсов
send_command('GET_RESOURCES:john')

# Получение информации о пользователе
send_command('GET_INFO:john')
