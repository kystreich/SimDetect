// Script to extract instructions and make array for opcode specs
// paste into https://evm.codes console
const extractInstruction = (row) => {
    const opcodeElem = row.querySelector("td.py-2.pr-6.uppercase > div");
    const nameElem = row.querySelector("td.py-2.pr-6:not(.uppercase) > div");
    if (!opcodeElem || !nameElem) return null;

    const name = nameElem.innerText.trim();
    const opcode = parseInt(opcodeElem.innerText.trim(), 16);
    if (isNaN(opcode)) return null;

    const stackInputs = name.startsWith("DUP") ? 1 : name.startsWith("SWAP") ? 2 : (row.querySelector("td:nth-child(4) > div")?.childElementCount ?? 0);
    const stackOutputs = name.startsWith("DUP") ? 2 : name.startsWith("SWAP") ? 2 : (row.querySelector("td:nth-child(5) > div")?.childElementCount ?? 0);
    const paramLookahead = name.startsWith("PUSH") ? (Number(name.slice(4)) || 0) : 0;

    return { name, opcode, stackInputs, stackOutputs, paramLookahead };
};

const toArray = (instructions) => {
    const table = Array.from({ length: 256 }, (_, i) => ({
        name: "INVALID",
        opcode: i,
        stackInputs: 0,
        stackOutputs: 0,
        paramLookahead: 0,
    }));

    for (const instr of instructions) {
        table[instr.opcode] = instr;
    }

    const fmt = (n) => n.toString(16).toUpperCase().padStart(2, "0");

    const entries = table
        .map((i) => `    /* 0x${fmt(i.opcode)} */ { "${i.name}", 0x${fmt(i.opcode)}, ${i.stackInputs}, ${i.stackOutputs}, ${i.paramLookahead} }`)
        .join(",\n");

    return `constexpr Instruction Instructions[INSTRUCTION_COUNT] = {\n${entries}\n};`;
};

const rows = [
    ...document.querySelectorAll(
        "#__next > div > main > section.py-10.md\\:py-20.bg-gray-50.dark\\:bg-black-700 > div > table > tbody > tr",
    ),
];

const instructions = rows.map(extractInstruction).filter(Boolean);
console.log(toArray(instructions));