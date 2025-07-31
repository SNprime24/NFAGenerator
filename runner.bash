g++ REtoNFA.cpp -o nfa.exe

./nfa.exe

node printAutomata.js nfa_diagram.mmd nfa_diagram.svg

echo "SVG generated: nfa_diagram.svg"