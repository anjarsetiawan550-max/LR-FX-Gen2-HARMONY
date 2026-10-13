# LR FX Gen 2 — Plate / Hall / Delay / Harmony (Standalone + VST3)

Plugin efek dengan GUI custom (aset PNG di folder `Assets/`), dibuat dengan JUCE 8 + CMake.

## Build lewat GitHub Actions
1. Upload isi folder ini ke repository GitHub (branch `main`).
2. Buka tab **Actions** → workflow **Build LR FX Gen 2** berjalan otomatis (atau jalankan manual via *Run workflow*).
3. Setelah selesai, unduh hasilnya di bagian **Artifacts** (Windows, macOS, Linux; masing-masing berisi zip VST3 + Standalone).
4. Untuk membuat Release otomatis: `git tag v1.0.0 && git push --tags`.

## Build lokal
```
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```
Hasil: `build/ReverbFX_artefacts/Release/{VST3,Standalone}`

## Kontrol
| Kontrol | Fungsi |
|---|---|
| LCD | Tipe FX, nomor + nama preset (`2 NamaPreset`), 4 LED tempo (merah, hijau, hijau, hijau), BPM |
| Down / Up | Home: pilih preset (lalu **klik kiri knop TYPE/PROGRAM** untuk load). Menu: geser baris parameter. Store: pilih slot |
| Utility | Panel Audio Input / Output (sama seperti LR PRO FX): pilih None / Channel 1 (L) / Channel 2 (R) untuk Input 1, Input 2, Output 1, Output 2. Tombol BACK / Menu / Exit menutup panel |
| Menu | Plate/Hall: Decay, PreDelay, Room, Diffusion, Damping, Low Cut, Hi Cut (20–20000 Hz, filter one-pole seperti LR PRO FX; default 80 Hz / 16 kHz). Delay: Time, Feedback, Hpf, Lpf. Harmony: Key (C–B), Mode (11 pilihan), Sharp (Major/Minor), Tone (Normal/Warm/Bright), Out (level fx, dB). Ubah nilai dengan roll mouse pada knop TYPE/PROGRAM (atau drag) |
| Exit | Kembali ke tampilan awal |
| Store | Popup nama preset; klik kiri knop TYPE/PROGRAM (atau Enter) untuk menyimpan ke slot (maks. 10) |
| TYPE/PROGRAM | Home: roll mouse = pilih Plate / Hall / Delay / Harmony |
| INPUT / MIX / OUTPUT | Level masuk / campuran dry-wet / level keluar |
| REV EQ | Low shelf ±18 dB @ 800 Hz, High shelf ±18 dB @ 8 kHz (pada sinyal efek) |
| TAP | Delay: tap tempo (klik atau **Spasi**), Delay Time = interval tap. Harmony: ganti **Sharp** Major <-> Minor. Tipe lain: tidak berfungsi |

## Tipe HARMONY
Mendeteksi nada suara (monofonik, 70–900 Hz), memetakannya ke tangga nada **Key + Major/Minor**, lalu membuat 1–2 suara harmoni diatonis.
Mode: `OCT-`, `5th L`, `3rd L`, `3rd H`, `5th H`, `OCT+` (satu suara) dan `OCT- & OCT+`, `5th L & 3rd H`, `5th L & 5th H`, `3rd L & 3rd H`, `3rd H & 5th H` (dua suara, kiri/kanan).
Terts/kuint mengikuti tangga nada (terts mayor atau minor tergantung nada yang dinyanyikan). Knop **MIX** tetap dry/wet; **Out** = level suara harmoni. Cocok untuk sumber monofonik (vokal / instrumen satu nada).

Preset tersimpan di `presets.xml` (folder data aplikasi pengguna, subfolder `ReverbFX`).
Slot 1–4 berisi preset contoh yang bisa ditimpa.

Catatan standalone: input audio dalam keadaan mute secara default (anti-feedback). Buka Utility → Audio/MIDI Settings
lalu hilangkan centang *Mute audio input*.

Lisensi: JUCE 8 memakai lisensi AGPLv3 / komersial — periksa ketentuannya sebelum mendistribusikan plugin.
