# NFA Generator from Regular Expression

This project converts a **Regular Expression (RE)** into a **Non-deterministic Finite Automaton (NFA)**.It is implemented in C++.

It generates a visual representation of the NFA using **Mermaid.js** and includes scripts to automate visualization via Node.js.

<br>


## 📚 Features

- Convert a regular expression to an NFA using Thompson's construction.
- Output the NFA structure in **DOT/Mermaid** format.
- Automatically generate an SVG diagram of the NFA using **Mermaid CLI**.
- Simple command-line interface for compiling and running the tool.

<br>

## 🛠️ Requirements

#### C++ Compiler
- `g++` : Compiles the C++ code 

#### Node.js and npm
- [Node.js](https://nodejs.org/) (v20 or above recommended)
- [Mermaid CLI](https://github.com/mermaid-js/mermaid-cli) :  Used to generate SVG diagrams from Mermaid Syntax


<br>


## 📄 File Overview and How to Run

The project consists of several key files, each with a specific purpose:

- **`REtoNFA.cpp`**: 

This is the main C++ program that takes a regular expression as input and constructs its equivalent NFA using Thompson's construction. It generates the NFA structure in Mermaid syntax and writes it to a file named `nfa_diagram.mmd`. To compile and run this file on Linux or macOS, use the following commands:

```bash
  g++ REtoNFA.cpp -o nfa && ./nfa
```

- **`printAutomata.js`**: 

This Node.js script takes the Mermaid-format .mmd file and uses the Mermaid CLI to convert it into an SVG diagram named nfa_diagram.svg. Run the script using:

```bash
  node printAutomata.js  nfa_diagram.mmd  nfa_diagram.svg 
  # will generate a svg file nfa_diagram showing the NFA diagram
```

- **`runner.bash`**: 

This is a convenience Bash script that automates the full process. 
It compiles REtoNFA.cpp, runs the program to generate nfa_diagram.mmd, and then calls printAutomata.js to produce svg diagram. This simplifies the workflow into a single command: **`(but works in LINUX or MAC system)`**

```bash
  bash runner.bash <diagram_name>   # will generate a <diagram_name>.svg showing the NFA diagram
  bash runner.bash                  # will generate a nfa_diagram.svg showing the NFA diagram
```

<br>

## 🚀 Usage

### LINUX / MAC :
1. **Install Dependencies** (this installs mermaid.js) : 
```bash
  npm install
```
2. Run the `runner.bash` script to generate the NFA and its SVG diagram : 
```bash
 bash runner.bash <diagram_name>
```
- `<diagram_name> (optional) : The base name of the output SVG file. defaults to nfa_diagram`

### WINDOWS : 
1. **Install Dependencies** (this installs mermaid.js) : 
```bash
  npm install
```
2. **Compile the C++ code** (assuming g++ is in your PATH) :
```bash
  g++ REtoNFA.cpp -o nfa.exe
  .\nfa.exe
```
3. **Run the Node.js visualizer** : 
```bash
  node printAutomata.js nfa_diagram.mmd <diagram_name>.svg
```
- `<diagram_name>: The base name of the output SVG file.

<br>


## 🙋‍♂️ Author
Suprit Naik (22CS01018)
