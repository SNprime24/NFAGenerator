import { run } from "@mermaid-js/mermaid-cli";

let inputFile = "nfa_diagram.mmd";
let outputFile = "nfa_diagram.svg";

const args = process.argv.slice(2);

if (args.length == 2) {
    inputFile = args[0];
    outputFile = args[1];
}else if (args.length == 1) {
    outputFile = args[0];
}

await run(
   inputFile,
   outputFile
)