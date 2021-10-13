#!/usr/bin/python

import subprocess

if __name__=="__main__":
	result = subprocess.check_output(['ls'])
	print(result)
