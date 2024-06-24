# Project-SoftwareEngineering 1BA UA

GUI voor dit project is geleverd met Qt, verander `CMAKE_PREFIX_PATH` in `CMakeLists.txt` zo dat deze verwijst naar je eigen Qt locatie.

Alternatief: GUI is aanwezig in Build folder. Run gewoon de .sh file en de GUI werkt zonder enige library op voorhand te installeren.

Voor enkel tests kan je gewoon de lijnen commenten in `CMakeLists.txt` die aangegeven staan. Dan compile je enkel voor debug_tests

Makefile kan zelf gebuild worden als nodig door:

```bash
cmake CMakeLists.txt
```

Targets kunnen gebuild worden met
```
make
```

| :exclamation:  Het kan zijn dat gtest libs moeten vervangen worden door eigen gebuilde libs   |
|-----------------------------------------------------------------------------------------------|
