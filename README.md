<p>
  <img src="https://img.shields.io/github/license/angpolito/Carsharing"/>
  <img src="https://img.shields.io/github/contributors/angpolito/Carsharing"/>
  <img src="https://img.shields.io/github/forks/angpolito/Carsharing"/>
  <img src="https://img.shields.io/github/stars/angpolito/Carsharing"/>
</p>

# Carsharing 🚗
**Carsharing** is a personal project in C developed for the course *Laboratorio di Informatica* (*Computer Laboratory*) during the 2022/2023 academic year, (1st year of the BSc program in *Computer Science*) at the *University of Bari Aldo Moro*.

> **Disclaimer**: This was my first project in C, so there may be mistakes, and the code could be better optimized. The project design and implementation were directly handled by Angelo Polito, while the project outline was conceived by the instructor. The implementation correctly meets the specified requirements.

---

## 📝 Project Description

Carsharing is a platform that allows drivers to upload trips and customers to book them. It is also possible to view driver ratings submitted by customers.

---

## 👨‍💻 Author

- **Author**: Angelo Polito
- **LinkedIn**: [@angelopolito](https://www.linkedin.com/in/angelopolito)

---

## ⚙️ Developed with
<img src="https://github.com/devicons/devicon/blob/master/icons/c/c-original.svg" title="C" alt="C" width="40" height="40"/>
<img src="https://img.shields.io/github/languages/top/angpolito/Carsharing?color=red"/>

---

## 🛠️ Technical Specifications

The code is divided into four main sections:

- `main.c`
- `gestione_guidatori.c` (header file: `gestione_guidatori.h`)
- `gestione_viaggi.c` (header file: `gestione_viaggi.h`)
- `visualizza_menu.c` (header file: `visualizza_menu.h`)

**Header files**:
- `gestione_guidatori.h`
- `gestione_viaggi.h`
- `visualizza_menu.h`
- `strutture.h`

There are also two `.bin` files used to permanently store data:

- `file_temporaneo.bin`
- `file_viaggi.bin`

---

## 🔧 Installation

To run the project, follow these steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/angpolito/Carsharing.git
   ```

2. Navigate to the project folder:

   ```bash
   cd Carsharing
   ```

3. Compile the project:

   ```bash
   gcc -o carsharing main.c gestione_guidatori.c gestione_viaggi.c visualizza_menu.c
   ```

4. Run the program:

   ```bash
   ./carsharing
   ```

---

## 📄 License

This project is licensed under the Eclipse Public License 2.0 - see the [LICENSE](LICENSE) file for details.

---

## Contributors
<a href="https://github.com/angpolito/Carsharing/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=angpolito/Carsharing" alt="contrib.rocks image" />
</a>

---

### 👀 Contributing

If you wish to contribute to this project, fork the repository, make your desired changes, and submit a pull request. I’ll be happy to review it!
