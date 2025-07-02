function CheckWav(filename)
    [y, Fs] = audioread(filename);
    fprintf('--- Информация о файле ---\n');
    fprintf('Название файла: %s\n', filename);
    fprintf('Частота дискретизации: %d Гц\n', Fs);
    fprintf('Длительность: %f сек\n', length(y)/Fs);
end