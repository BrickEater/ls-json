PURPOSE:
A CLI binary which outputs directory listings into JSON meant to be used for further rendering and customization.

EXAMPLE:
```json
$lsj
{
	"/home/user/Repos/projects/c/ls-json":	{
		"main.c":	{
			"is_dir":	0,
			"permissions":	"644",
			"mode":	33188,
			"inode":	27394049,
			"link_count":	1,
			"uid":	1000,
			"gid":	1000,
			"block_size":	4096,
			"file_size":	2261,
			"blocks":	8,
			"ctime":	1776053493,
			"atime":	1776279272,
			"mtime":	1776053493
		}
	}
}
```

INSTALL:
git clone https://github.com/BrickEater/ls-json.git
cd ls-json
python build.py
#mv ./build/lsj /usr/local/bin/lsj
