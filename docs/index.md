**Contributors:** {% for member in site.github.contributors %}<a href="{{member.html_url}}"><img src="{{member.avatar_url}}" width="32" height="32"></a>{% endfor %}

## Summary
Building using Cmake will produce ``hsat``, compiled code for executing the HSAT algorithm.

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

## Citations
1. McComb C, Cagan J, Kotovsky K. Drawing Inspiration From Human Design Teams for Better Search and Optimization: The Heterogeneous Simulated Annealing Teams Algorithm. ASME. J. Mech. Des. 2016;138(4):044501-044501-6. doi:10.1115/1.4032810.
2. McComb, Christopher, Jonathan Cagan, and Kenneth Kotovsky. "Heterogeneous Simulated Annealing Teams: An Optimizing Search Algorithm Inspired by Engineering Design Teams." International Conference on Engineering Design, Milan, Italy, July. 2015. doi:10.17605/OSF.IO/8K2CR.

## Acknowledgements
This material is based upon work supported by the National Science Foundation Graduate Research Fellowship under Grant No. DGE125252 and the United States Air Force Office of Scientific Research through grant FA9550-12-1-0374.
