
import serial
import mysql.connector
import argparse
from datetime import datetime

def novo_atendimento(user, pw, tag, paciente=1):
        try:
                conn = mariadb.connect(
                user=user,
                password=pw,
                host="localhost",
                port=3306,
                database="bancodedados"
                )

        except mariadb.Error as e:
                print("erro: {e}")
                sys.exit(1)
                
        cur = conn.cursor()
        try:
                timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
                cur.execute("INSERT INTO Atendimentos (diaHora, atividade, paciente) VALUES (?, ?, ?) RETURNING codigo", 
                (timestamp, "1a", 1))
                cod_atendimento = cur.fetchone()
                cur.execute("INSERT INTO AtendimentoProfEnf (codAtendimento, codProfEnf) VALUES (?, ?)", 
                (cod_atendimento, tag))
                
                print("atendimento registrado: " + tag)
        except mariadb.Error as e:
                print("erro: {e}")
        
def cadastrar_tag(user, pw, tag, nome, tipo):
        try:
                conn = mariadb.connect(
                user=user,
                password=pw,
                host="localhost",
                port=3306,
                database="bancodedados"
                )

        except mariadb.Error as e:
                print("erro: {e}")
                sys.exit(1)
                
        cur = conn.cursor()
        try:
                cur.execute("INSERT INTO ProfissionaisEnf (codigo, nome, tipo) values (?, ?, ?)", (tag, nome, tipo[0]))
                print("cadastrado: " + tag + ", " + nome)
        except mariadb.Error as e:
                print("erro: {e}")

if __name__ == "__main__":

        ser = serial.Serial('/dev/ttyUSB0')

        while True:
            if ser.in_waiting:
                #print("connected")
                bs = ser.read(ser.in_waiting)
                bs = '/'.join([f'0x{b:x}' for b in bs])
                bs = bs.removeprefix('0xcc/0xff/0xff/0x10/0x32/0xd/0x1/')
                lastchar = bs[-1]
                while lastchar != '/':
                        bs = bs[:-1]
                        lastchar = bs[-1]
                bs = bs[:-1] # remove '/'
                # print(bs)
                bs = bs.removeprefix('0x')
                temp = bs.split('/0x')
                tag = ''
                for i in temp:
                        if len(i)<2:
                                tag+='0'
                        tag += i
                print(tag)
                                
                parser = argparse.ArgumentParser()
                parser.add_argument("-c", "--cadastrar", type=int, metavar='int', help="1=cadastrar nova tag", default=0)
                parser.add_argument("-n", "--nome", type=str, help="nome do profissional de enfermagem")
                parser.add_argument("-t", "--tipo", type=str, help="e=enfermeiro ou t=tecnico")
                parser.add_argument("-u", "--username", type=str,  required=True, help="mariadb username")
                parser.add_argument("-p", "--password", type=str, required=True, help="mariadb password")
                args = parser.parse_args()
                cad = args.cadastrar
                nome = args.nome
                tipo = args.tipo
                user = args.username
                pw = args.password
                if cad == 1:
                cadastrar_tag(user, pw, tag, nome, tipo)
                        else:
                        novo_atendimento(user, pw, tag)
                

