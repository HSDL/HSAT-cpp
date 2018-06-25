**Contributors:** {% for member in site.github.contributors %}<a href="{{member.html_url}}"><img src="{{member.avatar_url}}" width="32" height="32"></a>{% endfor %}

## Summary
Building using Cmake will produce ``hsat``, compiled code for executing the HSAT algorithm.

## Options
<style>
.tablelines table, .tablelines td, .tablelines th {
        border: 1px solid black;
        }
</style>
| Flag                          | Description                                               |
|-------------------------------|---------|
| ``--bench``,``-b`` | Instructs the algorithm to benchmark the set of options in input. |
| ``--input file``, ``-i file`` | Denotes the input file for the algorithm. |
| ``--output file``, ``-o file`` | Denotes the output file for the algorithm. |
|  ``--pattern n``, ``-p n`` | Instructs the algorithm to perform a pattern search with n iterations to tune parameters. |
|  ``--univar n``, ``-u n`` | Instructs the algorithm to perform a stochastic univariate search with n iterations to tune parameters. |
|  ``--verbose``, ``-v`` | Verbose mode (lots of output). Limited integration at the moment. |
{: .tablelines}

## Citing This Work
1. McComb C, Cagan J, Kotovsky K. Drawing Inspiration From Human Design Teams for Better Search and Optimization: The Heterogeneous Simulated Annealing Teams Algorithm. ASME. J. Mech. Des. 2016;138(4):044501-044501-6. doi:10.1115/1.4032810.
2. McComb, Christopher, Jonathan Cagan, and Kenneth Kotovsky. "Heterogeneous Simulated Annealing Teams: An Optimizing Search Algorithm Inspired by Engineering Design Teams." International Conference on Engineering Design, Milan, Italy, July. 2015. doi:10.17605/OSF.IO/8K2CR.

## Acknowledgements
This material is based upon work supported by the National Science Foundation Graduate Research Fellowship under Grant No. DGE125252 and the United States Air Force Office of Scientific Research through grant FA9550-12-1-0374.
