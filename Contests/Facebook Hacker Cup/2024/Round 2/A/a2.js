import fs from "fs/promises";

const MAXD = 8;

const prefs = [...Array(MAXD + 1)].map(() => {
  return [];
});

const gen = (pref) => {
  prefs[pref.length].push(pref);
  const last = parseInt(pref[pref.length - 1]);
  if (pref.length == MAXD) return;
  for (let d = last; d <= 8; d++) {
    gen(pref + d);
  }
};

for (let d = 1; d <= 8; d++) {
  gen(d.toString());
}

const peaks = [...new Array(9)].map((_, i) => BigInt(i + 1));

for (let i = 1; i <= MAXD; i++) {
  for (const a of prefs[i]) {
    for (const b of prefs[i]) {
      const d = Math.max(parseInt(a[i - 1]), parseInt(b[i - 1]));
      for (let c = d + 1; c <= 9; c++) {
        peaks.push(BigInt(a + c + [...b].reverse().join("")));
      }
    }
  }
}

// console.log(peaks.length);
// console.log(peaks);
peaks.sort((a, b) => (a < b ? -1 : 1));

const lines = await fs
  .readFile(process.argv[2], "utf8")
  .then((data) => data.toString().split("\n"));

const T = parseInt(lines[0]);
for (let t = 1; t <= T; t++) {
  console.error(t);
  const [A, B, M] = lines[t].split(" ").map(BigInt);

  const find = (x) => {
    let l = 0,
      r = peaks.length - 1;
    while (l < r) {
      const m = (l + r) >> 1;
      if (peaks[m] >= x) {
        r = m;
      } else {
        l = m + 1;
      }
    }
    return l;
  };

  console.log(`Case #${t}: ${find(B + 1n) - find(A)}`);
}
