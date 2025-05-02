const createModule = require('./sort.js');

createModule().then((Module) => {
  // Redirect C++ stdout to Node.js console
  Module.print = console.log;
  Module.printErr = console.error;

  Module._main();  // Call the compiled main()
});
