% generate_core_code_class.m
% This script generates C++ code for the CLASS 'XTC_Processor'.
% This is the modern, recommended approach for MATLAB R2019b and newer.

% --- Configuration ---
frameSize   = 512;      % Tamaño de bloque de audio típico
numChannels = 2;        % Canales de audio (estéreo)

% 1. Define the type for the audio input ('in') to the step method.
% Le decimos a Coder que 'in' es una matriz de doubles, con un número
% variable de filas (Inf) pero siempre 2 columnas.
exampleInput = coder.typeof(zeros(frameSize, numChannels), [Inf, 2], [1, 0]);

% --- Code Generation Command ---
% Configuración básica para generar una librería C++
cfg = coder.config('lib');
cfg.TargetLang = 'C++';
cfg.GenerateReport = true; % Genera un informe útil para depuración

% Define the input arguments for the CLASS method to be compiled.
% En este caso, estamos compilando el método 'step', que toma un
% argumento ('in') después del objeto mismo.
args = {exampleInput};

% Execute codegen on the CLASS 'XTC_Processor'.
% MATLAB Coder will generate code for the class, its properties,
% constructor, and the step method.
disp('Iniciando la generación de código C++ para la clase...');
codegen -config cfg XTC_Processor -args args

disp('¡Generación de código completada!');
disp('Revisa la carpeta "codegen/lib/XTC_Processor" para ver los archivos C++ generados.');

