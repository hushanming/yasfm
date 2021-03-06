function fs = fguiButtonRunYASFM(fs, fn)

dataDir = fullfile(fs.DataDirectory,fs.DatasetSubdirectory);

if ~exist(dataDir,'dir')
    mkdir(dataDir);
end

command = [fs.YASFMExe ' ' dataDir ' ' fs.imgsSubdir ' ' ...
    num2str(fs.firstOctave) ' ' fs.ccdWidthDb];

system(command);

end