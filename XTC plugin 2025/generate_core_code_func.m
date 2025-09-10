% generate_core_code.m
% Este script genera c�digo C++ para la FUNCI�N 'xtc_processor_func'.
% Es compatible con MATLAB R2017b y versiones posteriores que soportan
% la generaci�n de c�digo para funciones con variables persistentes.

% --- Configuraci�n ---
frameSize   = 512;      % Tama�o de bloque de audio t�pico
numChannels = 2;        % Canales de audio (est�reo)
sampleRate  = 44100;    % Frecuencia de muestreo est�ndar

% 1. Definir los tipos y tama�os para la entrada de audio ('in')
% Le decimos a Coder que 'in' es una matriz de doubles, con un n�mero
% variable de filas (Inf) pero siempre 2 columnas.
exampleInput = coder.typeof(zeros(frameSize, numChannels), [Inf, 2], [1, 0]);

% 2. Definir la estructura para los par�metros SINTONIZABLES ('params')
% Esta estructura contiene los par�metros que se pueden cambiar en tiempo real.
% Notar que 'nSamplesIR' NO est� aqu�, ya que es una constante en la funci�n.
paramStruct = struct(...
    'D', 1.0, ...
    'dp', 0.2, ...
    'do', 0.18, ...
    'beta', 0.01, ...
    'SampleRate', sampleRate ...
);
exampleParams = coder.typeof(paramStruct);

% --- Comando de Generaci�n de C�digo ---
% Configuraci�n b�sica para generar una librer�a C++
cfg = coder.config('lib');
cfg.TargetLang = 'C++';
cfg.GenerateReport = true; % Genera un informe �til para depuraci�n

% Definir los dos argumentos de entrada para la funci�n
args = {exampleInput, exampleParams};

% Ejecutar codegen sobre la FUNCI�N 'xtc_processor_func'
disp('Iniciando la generaci�n de c�digo C++ para la funci�n...');
codegen -config cfg xtc_processor_func -args args

disp('�Generaci�n de c�digo completada!');
disp('Revisa la carpeta "codegen/lib/xtc_processor_func" para ver los archivos C++ generados.');