# PYTHML

## About

PYTHML (Python + HTML, yes it's stupid but someone already has dibs on PYHTML) is a programming tool that allows you to write Python code inside of HTML files. Currently in development.

## How to Write PYTHML

PYTHML is written in HTML files. The syntax is the same as HTML, but using the <python> tag, you can write Python code. The program formats and attempts to fix your HTML, for example, it will add the <!DOCTYPE html> if missing. Here is an example of a simple PYTHML file and its transition:

```html
<html lang="en">
<head>
</head>
<body>
<div>
<python>
    x = 3
    for i in range(x):
        print(f"<p>{i}</p>")
</python>
</div>
</body>
</html>
```


```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta name="generator" content=
  "HTML Tidy for HTML5 for Linux version 5.6.0">
  <title></title>
</head>
<body>
  <div>
    <p>0</p>
    <p>1</p>
    <p>2</p>
  </div>
</body>
</html>
```

## Currently Supported Features
Only basic Python code inside of the <python> tag is supported. 

Currently the program just runs whatever is inside the <python> tag (the python tag is case-insensitive) and replaces the tag with the output, but in the future, this program will run using something like pythml index.html which you can download via pip, won't rely on print() statements to generate html, allow for input variables in Python scripts, and more.

## How to use

Download the latest executable from the releases page. Run the executable and pass the path to the HTMLX executable as an argument. The program will then compile the HTMLX file into a normal HTML file.

## Future Plans

- [ ] Download package via pip
- [ ] Global syntax
- [ ] Allow for input variables via Python injection in scripts
- [ ] Render HTMLX files in Python using a custom library


