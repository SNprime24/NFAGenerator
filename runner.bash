g++ REtoNFA.cpp -o nfa.exe

./nfa.exe

mmdc -i nfa_diagram.mmd -o nfa_diagram.svg

echo "SVG generated: nfa_diagram.svg"