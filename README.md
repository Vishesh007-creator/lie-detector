# lie-detector# Lie Detector (Fun C Project)

This is a **console-based lie detector app** written in C.  
It does **not** detect real lies – it just estimates *stress / hesitation* based on:

- How long you take to answer
- How many words you type
- If you use hesitation phrases like:
  - `maybe`, `I think`, `not sure`, `shayad`, `kya pata` etc.

> ⚠️ **Disclaimer:** This project is for fun, learning and experiments only.  
> It is **not** scientifically accurate and must not be used for any serious decision-making.

---

## 🔧 Features

- Multiple questions asked one by one  
- Measures:
  - Typing time (in seconds)
  - Word count
  - Approx WPM (words per minute)
  - Hesitation word count
- Calculates a **stress score**
- Gives a final verdict:
  - `Likely Truthful ✅`
  - `Uncertain 😶`
  - `Possibly Lying ❌`

---

## 🖥️ How to Compile & Run

### Using GCC (Linux / Mac / WSL / Termux)

```bash
gcc lie_detector.c -o liedetector
./liedetector
