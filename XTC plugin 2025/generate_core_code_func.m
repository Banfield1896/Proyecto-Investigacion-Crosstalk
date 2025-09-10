% generate_core_code.m
% Este script genera código C++ para la FUNCIÓN 'xtc_processor_func'.
% Es compatible con MATLAB R2017b y versiones posteriores que soportan
% la generación de código para funciones con variables persistentes.

% --- Configuración ---
frameSize   = 512;      % Tamaño de bloque de audio típico
numChannels = 2;        % Canales de audio (estéreo)
sampleRate  = 44100;    % Frecuencia de muestreo estándar

% 1. Definir los tipos y tamaños para la entrada de audio ('in')
% Le decimos a Coder que 'in' es una matriz de doubles, con un número
% variable de filas (Inf) pero siempre 2 columnas.
exampleInput = coder.typeof(zeros(frameSize, numChannels), [Inf, 2], [1, 0]);

% 2. Definir la estructura para los parámetros SINTONIZABLES ('params')
% Esta estructura contiene los parámetros que se pueden cambiar en tiempo real.
% Notar que 'nSamplesIR' NO está aquí, ya que es una constante en la función.
paramStruct = struct(...
    'D', 1.0, ...
    'dp', 0.2, ...
    'do', 0.18, ...
    'beta', 0.01, ...
    'SampleRate', sampleRate ...
);
exampleParams = coder.typeof(paramStruct);

% --- Comando de Generación de Código ---
% Configuración básica para generar una librería C++
cfg = coder.config('lib');
cfg.TargetLang = 'C++';
cfg.GenerateReport = true; % Genera un informe útil para depuración

% Definir los dos argumentos de entrada para la función
args = {exampleInput, exampleParams};

% Ejecutar codegen sobre la FUNCIÓN 'xtc_processor_func'
disp('Iniciando la generación de código C++ para la función...');
codegen -config cfg xtc_processor_func -args args

disp('¡Generación de código completada!');
disp('Revisa la carpeta "codegen/lib/xtc_processor_func" para ver los archivos C++ generados.');