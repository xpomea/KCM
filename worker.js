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
      const result = sortStd();
      self.postMessage({ type: 'result', message: `sort_std() returned: ${result}` });
    }
  };
};