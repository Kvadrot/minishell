/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:18:05 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/08/27 21:20:19 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void appendToFile(const char *filename, const char *text) {
    // Otwieramy plik w trybie dopisywania (append mode)
    int fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);

    // Sprawdzamy, czy plik został poprawnie otwarty
    if (fd == -1) {
        write(STDERR_FILENO, "Imposible to open file", 22);
        exit(1);  // Zakończ program w przypadku błędu
    }

    // Dopisujemy tekst do pliku
    ssize_t bytes_written = write(fd, text, strlen(text));

    // Sprawdzamy, czy zapis się powiódł
    if (bytes_written == -1) {
        write(STDERR_FILENO, "Błąd przy zapisie do pliku\n", 27);
        close(fd);  // Zamykamy plik przed zakończeniem programu
        exit(1);
    }

    // Zamykamy plik
    close(fd);
}
