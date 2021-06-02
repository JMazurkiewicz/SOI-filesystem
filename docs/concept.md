# SOI - system plików

Autor: Jakub Mazurkiewicz (300226)

## Struktury

### Super blok

Super blok zostanie zrealizowany jako struktura o następujących polach:

```c
struct super_block {
    uint32_t magic; // 0x73766673
    uint32_t disk_size; // maksymalny teoretyczny rozmiar wirtualnego dysku: ~4GB
    
    uint32_t first_inode_offset; // "wskaźnik" na pierwszy inode
    uint32_t inode_count;
    uint32_t free_inode_count;
    
    uint32_t first_block_offset; // "wskaźnik" na pierwszy blok danych
    uint32_t block_count;
    uint32_t free_block_count;
};
// rozmiar: 32 bajty
// wyrównanie: 4 bajty
```

### INode

INode zostanie zrealizowany jako struktura o następujących polach:

```c
struct inode {
    char file_name[32];
    uint32_t file_size;
    uint32_t first_block_offset; // "wskaźnik" na pierwszy blok danych pliku
};
// rozmiar: 40 bajtów
// wyrównanie: 4 bajty
```

### Blok danych

Blok danych będzie zaimplementowany jako następująca struktura:

```c
#define BLOCK_SIZE ((int32_t)4096)

struct block {
    unsigned char memory[BLOCK_SIZE - sizeof(int32_t)];
    uint32_t next_block_offset; // "wskaźnik" na kolejny datablock
};
// rozmiar: BLOCK_SIZE (4096) bajtów
// wyrównanie: 4 bajty
```

## Implementowane funkcjonalności

Program obsługujący dysk wirtualny będzie wywoływany z linii komend. Będzie obsługiwał następujące instrukcje:

* `./svfs new <nazwa pliku> <rozmar>` - utworzenie nowego wirtualnego dysku,
* `./svfs copy from <virtual/native> to <native/virtual> <nazwa pliku>` - kopiowanie pliku o zadanej nazwie z dysku wirtualnego na natywny (lub odwrotnie),
* `./svfs print` - wyświetlanie katalogu dysku wirtualnego,
* `./svfs remove <nazwa pliku>` - usunięcie pliku o zadanej nazwie,
* `./svfs help` - wyświetlenie pomocy,
* `./svfs stats` - wyświetlanie statystyk (np. zajętości dysku).

## Testy

Testy zostaną napisane jako skrypty `.sh`. Będą one testować wyżej wymienione funkcjonalności - przykładowo, test sprawdzający prawidłowość kopiowania będzie sprawdzał, czy pliki (o różnych rozmiarach) zostały prawidłowo załadowane na dysk wirtualny oraz czy zostały z niego prawidłowo wczytane (porównanie rezultatów wykorzystaniem instrukcji `diff`).

## Narzędzia

| Narzędzie |      Wybór      |
| :-------: | :-------------: |
|  System   | Ubuntu 20.04  |
| Język | C99 |
| System budowania | CMake 3.10 |
| Kontrola wersji | git 2.29 ([Github](https://github.com/JMazurkiewicz/SOI-filesystem)) |
