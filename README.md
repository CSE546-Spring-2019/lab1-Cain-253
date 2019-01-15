# lab1-Cain-253
## Jeremy Cain

# Usage
Building: `make`
Running: `count.exe {input file path} {search string} {output file path}`
I could not get my project to work with binary in the time I provided myself (a new video game came out last Friday and I spent way too much time on it). It seems to work fine on strings, though.
Max file size depends on what your system defines as a long. Unlike reasonable programming languages, C doesn't even have consistent data types. Anything beyond a long will result in ftell failing to identify the file size, which will make the program quit.

#Sources
* Used VS Code with C code intellisense extension for code creation. https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools
* Used C-family doc generation for code docs. https://marketplace.visualstudio.com/items?itemName=alexcodercorp.comments
* Used classroom videos for help with C, since I've only barely ever used it before.
* Tried to use several other sources, but none of them were helpful.
