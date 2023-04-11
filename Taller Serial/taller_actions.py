# Universidad del Valle de Guatemala
# Carlos Gil 19443
# Taller Serial
# Ejercicio 2

from taller_gui import * #import mi archivo creado con el designer
from PyQt5 import QtWidgets
from PyQt5.QtGui import QPainter, QPen, QPixmap, QColor
import serial_taller as sc #importo mi archivo con las funciones que reciben, mapean y mandan datos
import threading
import serial
import time
import sys
direction = 0
class GUI (QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__ (self):
        super().__init__()
        self.setupUi(self)
        //metodos de cada objeto de la interfaz 
        self.textEdit.textChanged.connect(self.LED1)
        self.textEdit_2.textChanged.connect(self.LED2)
        self.dial.valueChanged.connect(self.SERVO1)
        self.dial_2.valueChanged.connect(self.SERVO2)
        self.textEdit_3.textChanged.connect(self.Load_vals)
        self.textEdit_4.textChanged.connect(self.STEPPER_steps)
        self.pushButton.clicked.connect(self.get_vals)
        self.radioButton.clicked.connect(self.STEPPER_dir)
        self.radioButton_2.clicked.connect(self.STEPPER_dir)
        self.update()
    //handlers que se llaman al accionar los metodos superiores
    def LED1(self):
        global direction
        sc.write(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
        print(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
    def LED2(self):
        global direction
        sc.write(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
        print(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
    def SERVO1(self):
        global direction
        sc.write(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
        print(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
    def SERVO2(self):
        global direction
        sc.write(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
        print(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
    def STEPPER_steps(self):
       global direction
       sc.write(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
       print(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
    def STEPPER_dir(self):
        global direction
        if (self.radioButton.isChecked()==True):
            direction = 0
        else:
            direction = 1
        sc.write(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
        print(f'<LED1={self.textEdit.toPlainText()},LED2={self.textEdit_2.toPlainText()},SERVO1={self.dial.value()},SERVO2={self.dial_2.value()},STEPS={self.textEdit_4.toPlainText()},DIR={direction}>')
    def Load_vals(self):
        global direction
        datos = self.textEdit_3.toPlainText()
        sc.write(f'<{datos}>')
        print(datos.split(","))
        try:
            if (int(datos.split(",")[5].split("=")[1])==1):
                    self.radioButton_2.setChecked(True)
                    direction =1
            else:
                    self.radioButton.setChecked(True)
                    direction = 0
            self.textEdit.setText(datos.split(",")[0].split("=")[1])
            self.textEdit_2.setText(datos.split(",")[1].split("=")[1])
            self.dial.setValue(int(datos.split(",")[2].split("=")[1]))
            self.dial_2.setValue(int(datos.split(",")[3].split("=")[1]))
            self.textEdit_4.setText(datos.split(",")[4].split("=")[1])
            
        except:
            pass
        
    def get_vals(self):
        self.label_9.setText(str(sc.read().decode()))
    def actualizar(self):
        self.update()


aplication = QtWidgets.QApplication([])
guimain=GUI()
guimain.show()
aplication.exec_()