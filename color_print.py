import colorama
from colorama import Style


class ColorPrint:
	def __init__(self) -> None:
		colorama.init()
	
	def setColor(self, color):
		print(Style.BRIGHT + color, end = '')
	
	def resetColor(self):
		print(Style.RESET_ALL, end = '')

	def __call__(self, *args, color = None, **kwds):
		self.resetColor()
		if color: self.setColor(color)
		print(*args, **kwds)
		self.resetColor()
