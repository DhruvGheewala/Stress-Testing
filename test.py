import os
import sys
import shutil
import zipfile
from colorama import Fore

from color_print import ColorPrint
from compile_run import Compiler, Runner

# *Create/update this file
# maybe bruteforce code
correct_code = './src/correct.cpp'

# *Create/update this file
# maybe optimal code missing some corner tests
incorrect_codes = ['./src/incorrect.cpp', './src/incorrect.cpp']
incorrect_codes = list(set(incorrect_codes))

# *Create/update this file
testcase_generator = './generator/testcase.cpp'
testcase_generator_linker = './generator/headers/generator_implementation.cpp'

# *All the corner cases where code gets different answer
# *from correct answer will be stored in this folder
testcase_root = './testcases'

shutil.rmtree(testcase_root)
os.mkdir(testcase_root)

compiler = Compiler()
runner = Runner()
print = ColorPrint()

color = {
	'red' : Fore.RED,
	'yellow' : Fore.YELLOW,
	'green' : Fore.GREEN,
	'cyan' : Fore.CYAN,
	'blue' : Fore.BLUE,
	'purple' : Fore.MAGENTA
}

def format(text):
	return '\n'.join([line.strip() for line in text.strip().split('\n') if line.strip() != '']).strip()

def compileFile(file_path, linkers = None):
	print('Compiling ', end = '')
	print(file_path, color = color['purple'])
	compiler.compile(file_path, linkers)
	print('Compilation done\n', color = color['cyan'])

def create_folder_zip(folder_path = testcase_root, zip_file_name = 'testcases'):
	ziph = zipfile.ZipFile(f'{zip_file_name}.zip', 'w', zipfile.ZIP_DEFLATED)
	for root, _dirs, files in os.walk(folder_path):
		for file in files:
			ziph.write(os.path.join(root, file))
	ziph.close()

def run_testcase(T):
	print(f'Case #{T}: ', end = '', color = color['yellow'])

	input = runner.run(testcase_generator).stdout.strip()
	correct_output = runner.run(correct_code, input).stdout
	correct_output = format(correct_output)

	wrong = False
	incorrect_outputs = []
	for incorrect_code in incorrect_codes:
		output = runner.run(incorrect_code, input).stdout
		output = format(output)
		incorrect_outputs.append(output)

	if len(set(incorrect_outputs + [correct_output])) == 1:
		print('Accepted', color = color['green'], end = '')
	else:
		wrong = True
		print('Wrong Answer: ', color = color['red'], end = '')
		print(end = '[')

	for index, output in enumerate(incorrect_outputs):
		print(end = ', ' if wrong and index > 0 else '')
		if output == correct_output:
			if wrong:
				print(index + 1, color = color['green'], end = '')
		else:
			print(index + 1, color = color['red'], end = '')

	print(']' if wrong else '')

	return {
		'wrong' : wrong,
		'input': input,
		'correct_output': correct_output,
		'incorrect_outputs': incorrect_outputs
	}

compileFile(testcase_generator, [testcase_generator_linker])
compileFile(correct_code)

for incorrect_code in incorrect_codes:
	compileFile(incorrect_code)

testcase_found = 0
print('Corner cases you need: ', color = color['blue'], end = '')
required_test = int(input())

testcase_threshold = 10000
for T in range(1, testcase_threshold + 1):
	try:
		result = run_testcase(T)
		if result['wrong']:
			required_test -= 1
			testcase_found += 1

			os.mkdir(f'{testcase_root}/{testcase_found}')
			with open(f'{testcase_root}/{testcase_found}/in.txt', 'w') as file:
				file.write(result['input'])

			with open(f'{testcase_root}/{testcase_found}/correct-output.txt', 'w') as file:
				file.write(result['correct_output'])

			for index, output in enumerate(result['incorrect_outputs']):
				if output != result['correct_output']:
					with open(f'{testcase_root}/{testcase_found}/incorrect-output-{index + 1}.txt', 'w') as file:
						file.write(output)

			if required_test == 0:
				create_folder_zip(testcase_root)
				print(f'Generated testcase in {testcase_root}')
				sys.exit(0)

	except KeyboardInterrupt:
		create_folder_zip(testcase_root)
		print('\n\nERROR: Operation cancelled by user', color = color['red'])
		sys.exit(1)
