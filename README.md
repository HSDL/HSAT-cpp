# HSAT [![Build Status](https://travis-ci.org/cmccomb/HSAT.svg?branch=master)](https://travis-ci.org/cmccomb/HSAT)

## Summary
Building using Cmake will produce   ``hsat``, compiled code for executing the HSAT algorithm.

## Options
<table>
<tr><th width=150>Flag</th><th>Description</th>
<tr>
  <td><tt>--bench</tt><br/><tt>&nbsp;-b file</tt></td>
  <td>Instructs the algorithm to benchmark the set of options in input.</td>
</tr>
<tr>
  <td><tt>--input file</tt><br/><tt>&nbsp;-i file</tt></td>
  <td>Denotes the input file for the algorithm. </td>
</tr>
<tr>
  <td><tt>--output file</tt><br/><tt>&nbsp;-o file</tt></td>
  <td>Denotes the output file for the algorithm.</td>
</tr>
<tr>
  <td><tt>--pattern n</tt><br/><tt>&nbsp;-p n</tt></td>
  <td>Instructs the algorithm to perform a pattern search with n iterations to tune parameters.</td>
</tr>
<tr>
  <td><tt>--univar n</tt><br/><tt>&nbsp;-u n</tt></td>
  <td>Instructs the algorithm to perform a stochastic univariate search with n iterations to tune parameters.</td>
</tr>
<tr>
  <td><tt>--verbose</tt><br/><tt>&nbsp;-v</tt></td>
  <td>Verbose mode (lots of output). Limited integration at the moment.</td>
</tr>
</table>
