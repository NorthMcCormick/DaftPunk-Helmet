angular.module('starter.controllers', [])

.controller('AppCtrl', function($scope, $ionicModal, $timeout) {

	// With the new view caching in Ionic, Controllers are only called
	// when they are recreated or on app start, instead of every page change.
	// To listen for when this page is active (for example, to refresh data),
	// listen for the $ionicView.enter event:
	//$scope.$on('$ionicView.enter', function(e) {
	//});

	// Form data for the login modal
	$scope.loginData = {};

	// Create the login modal that we will use later
	$ionicModal.fromTemplateUrl('templates/login.html', {
		scope: $scope
	}).then(function(modal) {
		$scope.modal = modal;
	});

	// Triggered in the login modal to close it
	$scope.closeLogin = function() {
		$scope.modal.hide();
	};

	// Open the login modal
	$scope.login = function() {
		$scope.modal.show();
	};

	// Perform the login action when the user submits the login form
	$scope.doLogin = function() {
		console.log('Doing login', $scope.loginData);

		// Simulate a login delay. Remove this and replace with your login
		// code if using a login system
		$timeout(function() {
			$scope.closeLogin();
		}, 1000);
	};
})

.controller('PlaylistsCtrl', function($scope, $timeout) {
	$scope.devices = [];
	$scope.isScanning = false;
	console.log("TEST");

	$scope.stopScanning = function(id) {
		//ble.stopScan();
	}

	$scope.scan = function() {
		if(!$scope.isScanning) {
			$scope.isScanning = true;
			$timeout(function() {
				$scope.devices = [];
				console.log("Start Scan");
				/*ble.scan([], 10, function(newDevice) {
					console.log(newDevice);
					$scope.devices.push(newDevice);
				}, failure);*/
				try {
					ble.startScan([], function(newDevice) {
						console.log("Device: " + JSON.stringify(newDevice));
						$scope.devices.push(newDevice);
						$scope.$apply();
					}, function(error) {
						console.log("Could not discover: " + error);
					});
				}catch(e) {
					console.log("Failed to scan" + e);
				}
			}, 500);

			$timeout(function() {
				ble.stopScan();
				$scope.isScanning = false;
			}, 
			5000);
		}
	}

	$scope.scan();

})

.controller('PlaylistCtrl', function($scope, $stateParams) {
	$scope.isConnected = false;
	$scope.service = '';
	$scope.characteristic = '';

	function stringToBytes(string) {
	   var array = new Uint8Array(string.length);
	   for (var i = 0, l = string.length; i < l; i++) {
	       array[i] = string.charCodeAt(i);
	    }
	    return array.buffer;
	}

	$scope.sendToggle = function() {
		ble.writeWithoutResponse($stateParams.deviceid, $scope.service, $scope.characteristic, stringToBytes('V'), function(){}, function(){});
	}

	$scope.sendFace = function(face) {
		ble.writeWithoutResponse($stateParams.deviceid, $scope.service, $scope.characteristic, stringToBytes('F' + face), function(){}, function(){});
	}

	$scope.$on('$ionicView.beforeEnter', function() {
		$scope.isConnected = false;
		$scope.service = '';
		$scope.characteristic = '';

		console.log("Attempting connection");

		try {
			ble.connect($stateParams.deviceid, function(results) {
				console.log("Connected");
				console.log(results);
				$scope.isConnected = true;

				$scope.service = '713D0000-503E-4C75-BA94-3148F18D941E';
				$scope.characteristic = '713D0003-503E-4C75-BA94-3148F18D941E';
				$scope.$apply();
			}, function(error) {
				console.log("Not connected");
				console.log(error);
				$scope.isConnected = false;
			});
		} catch(e) {
			console.log("Error: ");
			console.log(e);
		}
	});

});
