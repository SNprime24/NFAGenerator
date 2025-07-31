g++ REtoNFA.cpp -o nfa.exe
./nfa.exe

outputBase="$1"
if [ -z "$outputBase" ]; then
  outputBase="nfa_diagram"
fi

node printAutomata.js nfa_diagram.mmd "$outputBase.svg"

echo "SVG generated: nfa_diagram.svg"