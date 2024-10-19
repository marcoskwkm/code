import fs from "fs/promises";

const peaks = [];

for (let s = 1n; s <= 9n; s++) {
  let pref = s.toString();
  peaks.push(s);
  for (let d = s + 1n; d <= 9n; d++) {
    const s = d.toString();
    peaks.push(BigInt(pref + s + [...pref].reverse().join("")));
    pref += s;
  }
}

const lines = await fs
  .readFile(process.argv[2], "utf8")
  .then((data) => data.toString().split("\n"));

const T = parseInt(lines[0]);
for (let t = 1; t <= T; t++) {
  const [A, B, M] = lines[t].split(" ").map(BigInt);
  console.log(
    `Case #${t}: ${peaks.filter((p) => p % M == 0 && A <= p && p <= B).length}`
  );
}
