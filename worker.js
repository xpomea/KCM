importScripts('test_module.js'); // Load the WASM module

// Ensure Module is defined (Emscripten's code should already define it)
if (!Module) {
  Module = {};
}

// Add onRuntimeInitialized hook to the existing Module
Module.onRuntimeInitialized = () => {
  console.log('WASM module loaded in worker');

  const sortStd = Module.cwrap('sort_std', 'number', []);

  // Listen for messages from the main thread
  self.onmessage = function(e) {
    if (e.data.type === 'run') {
      // Clear output
      self.postMessage({ type: 'log', message: 'init' });

      // Redirect Module.print and Module.printErr to send messages back to the main thread
    //   const origPrint = Module.print || (() => {});
    //   const origPrintErr = Module.printErr || (() => {});

    //   Module.print = (text) => {
    //     self.postMessage({ type: 'log', message: text });
    //   };

    //   Module.printErr = (text) => {
    //     self.postMessage({ type: 'log', message: text });
    //   };

      try {
        const result = sortStd();
        self.postMessage({ type: 'result', message: `sort_std() returned: ${result}` });
      } catch (error) {
        self.postMessage({ type: 'log', message: `Error: ${error.message}` });
      }

      // Restore original functions
    //   Module.print = origPrint;
    //   Module.printErr = origPrintErr;
    }
  };
};