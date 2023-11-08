# Simplified blockchain simulation

## v0.2

### Realizuotas supaprastintas centralizuotas blockchain.
- Hash'avimo procesui naudota pirmame darbe sukurta hash funkcija.
- Realizuota merkle hash funkcija.
- Programoje naudojamos 3 klasės: user, transaction ir block tipo objektams.
- Blockchain, tinklo dalyvių sąrašas ir tranzakcijų pool saugomi vector tipo konteineriuose.

### Programos veikimas:
- Programa sugeneruoja 1000 atsitiktinių tinklo dalyvių ir išveda jų duomenis į failą.
- Programa sugeneruoja 10000 atsitiktinių tranzakcijų ir išveda jų duomenis į failą.
- Programa sukuria pirmąjį (genesis) bloką.
- Programa simuliuoja naujų blokų 'mining' procesą su 5 miners: A, B, C, D, E.
- Programos veikimo metu atspausdinamas kiekvieno naujai sukurto bloko header.
- Simuliacija baigiasi kai tranzakcijų pool'e nebelieka pakankamai tranzakcijų naujam blokui.
- Programos gale viso blockchain duomenys išvedami į failą.
- Į failą taip pat išvedami tiklo vartotojai su atnaujintais balansais.



