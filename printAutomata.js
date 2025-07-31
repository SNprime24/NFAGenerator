import { run } from "@mermaid-js/mermaid-cli"

const inputFile = process.argv[2]; 
const outputFile = process.argv[3];

if (!inputFile || !outputFile) {
    console.error("Usage: node printAutomata.js <inputFile> <outputFile>");
    process.exit(1);
}

await run(
   inputFile,
   outputFile
)