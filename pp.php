<?php
	
	$data = file("input.csv");
	$vertex = [];
	$lines = [];
	$res_vertex = [];
	$f_out = fopen("vertex.obj","w+");	
	array_shift($data);

	for ($i = 0; $i < count($data); $i++) { 
		$v = explode(";", $data[$i]);
		$lines[$v[0]][] = ['x' => $v[2],
						   'y' => $v[3]];
		// print_r($line);
		// fwrite($f_out, $v[0]."\n");
	}

	$l = 0.0001;
	foreach ($lines as $line) {
		foreach ($line as $point) {
			fprintf($f_out, "v %f %f %f\n", $point['x'] - $l , $point['y'] - $l , 0);	
			fprintf($f_out, "v %f %f %f\n", $point['x'] + $l , $point['y'] + $l , 0);			
		}	
	}
	fprintf($f_out, "#-------------------------\n");
	$k = 0;
	foreach ($lines as $line) {	
		fprintf($f_out, "f %d %d %d %d\n",1 + $k, 2 + $k, 4 + $k, 3 + $k);
		$k += 4;
	}
	

	fclose($f_out);

?>