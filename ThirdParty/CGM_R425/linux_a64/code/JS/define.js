/**
DASSAULT SYSTEMES
@author Damien Gleizes
*/

(function (exports, process) {

    var config = { paths: process.paths || [], async: true };     	 //configurable properties

    var modules = {};                              	                //Loaded module list
    var registeredModules = {};                                     //Registered module list
    var requireQueue = []; 							                //JS async load queue
    var dependencies = {};  						                //Used for checking ciruclar dependencies
    var loadedFiles = {};        					                //Loaded file cache         
	var urlFiles = {};												//URL files
    var keywords = ["require", "exports", "module"];                //Special dependencies keywords
    var runningID;													//JS running ID

    /**
    Helper
    */
    function indexOfInArray(oneArray, a, b, c, r) {
        for (b = oneArray, c = b.length, r = -1; ~c; r = b[--c] === a ? c : r);
        return r;
    };

    function isHereInArray(oneArray, elem) {
        return indexOfInArray(oneArray, elem) != -1;
    }

    function isArray(a) {
        return a instanceof Array;
    }

    /** 
    * Normalizes a path/url, cleaning up duplicate slashes,
    * takes care of `../` and `./` parts
    */
    function normalize(path, prevPath) {
        // Replace any matches of "./"  with "/"
        path = path.replace(/(^|[^\.])(\.\/)/g, "$1");

        // Replace any matches of "some/path/../" with "some/"
        while (prevPath !== path) {
            prevPath = path;
            path = path.replace(/([\w,\-]*[\/]{1,})([\.]{2,}\/)/g, "");
        }

        // Replace any matches of multiple "/" with a single "/"
        return path.replace(/(\/{2,})/g, "/");
    }

    /** 
    * Given a path and context (optional), will normalize the url
    * and convert a relative path to an absolute path.
    */
    function resolve(path, context) {

        //If path does not start with a "." it's relative to the base URL.
        context = (path.indexOf(".") !== 0) ? "" : context;

        //Never resolve "require", "module" and "exports" to absolute paths
        //For plugins, only resolve the plugin path, not anything after the first "!"
        if (isHereInArray(keywords, path) || ~path.indexOf("!")) {
            return path.replace(/([\d,\w,\s,\.\/]*)(?=\!)/, function ($0, $1) {
                return resolve($1, context);
            });
        }

        return normalize((context ? context + "/" : "") + path);
    }

    /**
    Takes an array as the first argument, and an object as the second.
    Replaces any values found in the array, with values in the object.
    */
    function swapValues(arr, obj) {
        for (var i in obj) {
            var j = indexOfInArray(arr, i);
            if (j != -1) {
                arr[j] = obj[i];
            }
        }
        return arr;
    }

    /** 
    Similar to UNIX dirname, returns the parent path of another path.
    */
    function getContext(path) {
        return path.substr(0, path.lastIndexOf("/"));
    }

    /**
    Gets the module by `id`
    */
    function getModule(id) {

        //Skip special keywords - replaced later by real values
        if (isHereInArray(keywords, id)) {
            return id;
        }

        //Search the cache
        var ns = modules;
        var parts = id.split("/");

        for (var i = 0, l = parts.length; i < l; i++) {
            var pi = parts[i];

            //Module not defined yet
            if (!ns[pi]) {
                return 0;
            }
            ns = ns[pi];
        }

        //return the found module
        return ns;
    }

    /**
    Gets the module by `id`
    */
    function addModule(id, def) {

        //Skip special keywords - replaced later by real values
        if (isHereInArray(keywords, id)) {
            return;
        }

        var ns = modules;
        var parts = id.split("/");

        for (var i = 0, l = parts.length; i < l; i++) {

            var pi = parts[i];

            //Store the module definition
            if (i == l - 1) {
                ns[pi] = def;
                return;
            }

            ns[pi] = ns[pi] || {};
            ns = ns[pi];
        }
    }

    /**
    */
    function loadFile(id) {
        process.jsopen(id,
						config.paths,
						function (path) { runningID = id; urlFiles[id] = 'file:///' + path.replace(/\\/g,'/'); },
						function () { runningID = undefined; },
						function () { runningID = undefined; throw new Error("'" + id + "' failed to load."); },
                        config.async);
    }

    /** 
    Does all the loading of js.
    */
    function loadModules(deps, callback, context) {

        //Add this require to the require queue
        var q = { m: deps, cb: callback };
        requireQueue.push(q);

        //Trigger dependencies loading
        for (var i = 0; i < deps.length; i++) {

            var dep = deps[i];
            if (~dep.indexOf("!")) {
                //If the module id has a "!"" in it, it's a plugin...
                loadPluginModule(dep, context, q, i);
                continue;
            }

            //if the file has not been loaded and module not defined, do the load
            if (!getModule(dep) && !loadedFiles[dep]) {
                if (!loadModule(dep)) {
                    loadFile(dep);
                }
            }
            loadedFiles[dep] = 1;
        }
    }

    /** 
    Loop through all of the items in requireQueue and if all modules in a given
    queue are defined, call the callback function associated with the queue.
    Called at the end of a define factory call
    */
    function handleRequireQueue() {

        var q;
        for (var i = requireQueue.length - 1; ~i && (q = requireQueue[i]) ; i--) {

            var ready = 1;
            for (var j = q.m.length - 1; ~j && ready; j--) {
                ready = getModule(q.m[j]);
            }

            if (ready) {
                requireQueue.splice(i, 1);
                require(q.m, q.cb);
            }
        }
    }

    /** 
    Loop through all of the items in requireQueue and for every registered module but not loaded yet, load the module.
    Called at the end of a define call
    */
    function handleDefineQueue() {

        var q;
        for (var i = requireQueue.length - 1; ~i && (q = requireQueue[i]) ; i--) {

            for (var j = q.m.length - 1; ~j; j--) {
                if(!getModule(q.m[j])) {
                    loadModule(q.m[j]);
                }
            }
        }
    }

    /**
    Stores dependencies for this module id and defines circular dependant modules
    */
    function handleCircularReferences(id, deps) {

        dependencies[id] = deps;

        //Check for any dependencies that have circular references back to this module
        for (var i = 0; i < deps.length; i++) {

            //Parse subdeps
            var d = deps[i];
            var subDeps = dependencies[d] || [];
            for (var j = 0; j < subDeps.length; j++) {

                var sd = subDeps[j];
                if (!isHereInArray(deps, sd)) {

                    //Circular reference detected
                    if (sd === id) {

                        // define circular references as empty modules to be defined later
                        addModule(d, { exports: {} });
                    }
                        //Add to the deps list
                    else {

                        deps.push(sd);
                    }
                }
            }
        }

    }

    /** 
    Used for loading and getting plugin-type modules
    */
    function loadPluginModule(module, context, q, moduleIndex) {

        /** 
        * Set the plugin path. Plugins are stored differently than normal modules
        * Essentially they are stored along with the context in a special "plugins"
        * property. This allows modules to lookup plugins with the sync require("index!./foo:./bar") method
        */
        var pluginPath = (context ? context + "/" : "") /*+ "plugins/"*/ + module.replace(/\//g, "_");

        //Let's check to see if the module is already defined
        var definition = getModule(pluginPath);

        /*
        * If no load queue is specified, then this function was invoked from require()
        * Return whether or not the plugin has been defined yet.
        * If the plugin is defined, no need to do anything else, so return.
        */

        if (!q || definition) {
            return definition;
        }

        //Update the path to this plugin in the queue
        q.m[moduleIndex] = pluginPath;

        module = module.split("!");
        var plugin = module.splice(0, 1)[0];

        module = module.join("!");

        //Let's make sure the plugin is loaded before we do anything else.
        require(plugin, function (pluginModule) {

            //If the plugin module has a normalize() method defined, use it
            module = pluginModule.normalize ?
                pluginModule.normalize(module, function (path) {
                    return resolve(path, context);
                }) :
                normalize(module);

            function load(module) {
                addModule(pluginPath, module);
                handleRequireQueue();
            }

            load.fromText = function (name, definition) {

                //Update the module path in the load queue with the newly computed module id
                q.m[moduleIndex] = pluginPath = name;

                /*jslint evil: true */
                new Function(definition)();
            };

            return pluginModule.load(
                module,
                require.localize(getContext(plugin)),
                load,
                config[plugin] || {}
            );
        });
    }

    function registerModule(id, deps, factory) {
        registeredModules[id] = { deps: deps, factory: factory, loading: false };
    }

    function onDepsLoaded(id, deps, factory) {
        var context = getContext(id);
        var module = getModule(id);
        module = module || { exports: {} };
        module.id = id;

        if (typeof factory === "function") {

            //If the factory is a function, we need to invoke it.
            //First let's swap "require", "module" and "exports" with actual objects
            var facArgs = swapValues(
                deps.length ? deps : (keywords.slice(0, factory.length)),
                {
                    "require": require.localize(context),
                    "module": module,
                    "exports": module.exports
                }
            );

            //In some scenarios, the global require object might have slipped through,
            //If so, replace it with a localized require.
            //var ri = facArgs.indexOf(require);
            //if (~ri) {
            //            facArgs[ri] = require.localize(context);
            //}

            //Use the factory return value as module value, otherwise keep the export
            module.exports = factory.apply(factory, facArgs) || module.exports;
        }
        else {
            //If the factory is not a function, set module.exports to whatever factory is
            module.exports = factory;
        }

        //Store the create module
        addModule(id, module);

        //Remove the registered module
        delete registeredModules[id];

        //Clear the dependencies from the _dependencies object (circular already resolved)
        delete dependencies[id];

        //Finally check the require queue if any cb can now be triggered with full dep loaded
        handleRequireQueue();
    }

    function loadModule(id) {
        var registeredModule = registeredModules[id];
        var result = Boolean(registeredModule);
        if (result && !registeredModule.loading) {
            registeredModule.loading = true;
            var context = getContext(id);
            var deps = registeredModule.deps;
            var factory = registeredModule.factory;

            //Convert relative path to absolut path
            for (var i = 0; i < deps.length; i++) {
                deps[i] = resolve(deps[i], context);
            }

            //First resolve circular references
            handleCircularReferences(id, deps.slice(0));

            require(deps, function () {
                onDepsLoaded(id, Array.prototype.slice.call(arguments, 0), factory);
            }, context);
        }
        return result;
    }

    /**
    Define modules. AMD-spec compliant.
    define(id, [], factory);
    define([], factory);
    define(id, factory);
    */
    function define(id, deps, factory) {

        //No id means that this is an anonymous module: define([],factory)
        if (typeof id !== 'string') {

            //Check this module is loaded by a require call
            if (runningID === undefined) {
                throw new Error("Anonymous modules must be defined within a require call");
            }

            factory = deps;
            deps = id;
            id = runningID;
        }

        //define(id, factory)
        if (!isArray(deps)) {
            factory = deps;
            deps = [];
        }

        //No dependencies, but the factory function is expecting arguments?
        //This means that this is a CommonJS-type module...
        if (!deps.length && factory.length && typeof factory === "function") {

            //Let's check for any references of sync-type require("moduleID")
            factory.toString()
                .replace(/(\/\*([\s\S]*?)\*\/|([^:]|^)\/\/(.*)$)/mg, "") // Remove any comments first
                .replace(/(?:require)\(\s*["']([^'"\s]+)["']\s*\)/g, // Now let's check for any sync style require("module") calls

                    function ($0, $1) {
                        if (deps.indexOf($1) < 0) {
                            /**
                            * We're not actually replacing anyting inside factory.toString(),
                            * but this is a nice, clean, convenient way to add any
                            * sync-type require() matches to the dependencies array.
                            */
                            deps.push($1);
                        }
                    }
                );

            deps = (keywords.slice(0, factory.length)).concat(deps);
        }

        registerModule(id, deps, factory);

        //Finally check the require queue if any define factory can now be triggered
        handleDefineQueue();
    }

    /**
    require(['dep', 'dep2', ...], callback)
    require('dep')
    */
    function require(deps, callback, context) {

        //No callback: require('dep')
        //Get the module from cache
        if (!callback) {

            deps = resolve(deps, context);
            var module = getModule(deps);
            if (!module) {
                module = loadPluginModule(deps, context);
                if (module) {
                    return module;
                }
                throw new Error("'" + deps + "' is not defined.");
            }

            return module.exports;
        }

        deps = (!isArray(deps)) ? [deps] : deps;
        var modules = [];


        for (var i = 0; i < deps.length; i++) {

            //Convert relative path to absolut path
            deps[i] = resolve(deps[i], context);

            //Get cached module
            var module = getModule(deps[i]);
            modules.push(module ? (module.exports ? module.exports : module) : 0);
        }

        //Load undefined modules
        if (isHereInArray(modules, 0)) {
            loadModules(deps, callback, context);
        }
            //Otherwise invoke the given callback
        else {
            callback.apply(exports, swapValues(modules, { "require": require }));
        }
    }

    /**
    * Returns a localized version of require, so that modules do not need
    * to specify their own id, when requiring relative modules, or resolving relative urls.
    */
    require.localize = function (context) {

        function localRequire(ids, callback) {
            return require(ids, callback, context);
        }

        localRequire.toUrl = function (id) {
            return require.toUrl(id, context);
        };

        return localRequire;
    };

	require.toUrl = function (id) {
		return urlFiles[id];
	};
	
    /**
    Configure require
    - paths
    */
    require.config = function (obj) {
        config = obj || {};
    };

    Object.defineProperty(require, "paths", {
        get: function () { return config.paths; },
        set: function (p) { config.paths = p; }
    });
    Object.defineProperty(require, "async", {
        get: function () { return config.async; },
        set: function (a) { config.async = a; }
    });

    Object.defineProperty(require, "__loadedFiles", {
        get: function () { return Object.keys(loadedFiles); },
        set: function () { }
    });

    /**
    Define global define and require methods.
    */
    exports.define = exports.define || define;
    exports.require = exports.require || require;

})(this, process);
