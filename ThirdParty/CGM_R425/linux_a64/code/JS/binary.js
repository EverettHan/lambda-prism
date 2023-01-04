define(function () {
    return {
		/**
		Do the core module loading 
		uses process.dlopen to load a DLL
		*/
        load: function (name, req, onload, config) {
				
				//Create a new module
				var module = {exports:{}};
				module.id = name;
          try {
            module.exports = process.dlopen(module, name);
          }
          catch (e) {
            process.displayException(e);
          }
				
				//Save the module to cache
				onload(module);
        }
    };
});


