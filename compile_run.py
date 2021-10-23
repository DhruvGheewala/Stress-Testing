import subprocess

py_extensions = ["py"]
cpp_extensions = ["cpp", "c", "cc"]

class Compiler:
	def __init__(self):
		self.cpp_cmd = 'g++ -std=c++{std} -DONLINE_JUDGE "{file_path}" -o "{file}.exe"'
		self.cpp_with_linker_cmd = 'g++ -std=c++{std} -DONLINE_JUDGE "{file_path}" "{linkers}" -o "{file}.exe"'

		self.java_cmd = "javac {file_path}"

	def get_compilation_cmd(self, file_path, linkers = None):
		file, lang = file_path.rsplit('.', 1)
		if lang in cpp_extensions:
			if linkers:
				space_separeted_linkers = '" "'.join(linkers)
				return self.cpp_with_linker_cmd.format(
					std = 17,
					file_path = file_path,
					linkers = space_separeted_linkers,
					file = file
				)

			return self.cpp_cmd.format(std = 17, file_path = file_path, file = file)

		return None # !Not yet included

	def compile(self, file_path, linkers = None):
		cmd = self.get_compilation_cmd(file_path, linkers)
		subprocess.run(cmd, check = True, shell = True)


class Runner:
	def __init__(self):
		self.cpp_cmd = '"{file}.exe"'
		self.python_cmd = 'python "{file}.py"'

	def get_run_cmd(self, file_path):
		file, lang = file_path.rsplit('.', 1)
		if lang in cpp_extensions:
			return self.cpp_cmd.format(file = file)

		if lang in py_extensions:
			return self.python_cmd.format(file = file)

		return None # !Not yet included

	def run(self, file_path, input = None):
		cmd = self.get_run_cmd(file_path)
		return subprocess.run(
			cmd,
			text = True,
			check = True,
			shell = True,
			input = input,
			capture_output = True
		)
