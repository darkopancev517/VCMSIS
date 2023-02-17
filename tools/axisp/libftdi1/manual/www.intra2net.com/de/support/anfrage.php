
<!doctype html>
<html lang="de">
<head>
<meta charset="utf-8">
<title>Intra2net &raquo; Support-Anfrage</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<link rel="stylesheet" type="text/css" media="screen" href="../screen.css">
<link rel="stylesheet" type="text/css" media="print" href="../print.css">
</head>

<body>

<!-- header start -->

<div id="header">

<div id="logo">
	<a href="../index.html">
		<div id="logo_screen"><img src="../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="anfrage.php#navigation"><div class="mobilemenu"><img src="../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="anfrage.php#"><div class="mobilemenu"><img src="../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../produkte/intranator.php">Business Server</a></li>
						<li><a href="../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../produkte/network_security.php">Network Security</a></li>
						<li><a href="../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../download/index.php">Software</a></li>
			<li><a href="../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="anfrage.php">Support-Anfrage</a></li>
			<li><a href="handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="antispam/index.html">Blacklist Performance</a></li>
			<li><a href="schulung.php">Schulung</a></li>
			<li><a href="fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../kaufen/index.php">Partner finden</a></li>
			<li><a href="../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->


            <form action="anfrage.php" method="post" name="supportform1" id="supportform1">
             <table class="long_form">
                          <tr><th colspan="2"><h2>Intra2net Support-Anfrage - Schritt 1 von 2</h2></th></tr>
             <tr><td></td><td style="padding: 0px;"><img src="../pictures/form_pointer.gif" style="display: block;"></td></tr>
              <tr>
                  <td valign="top">Lizenz<span class="required">*</span>
                  </td>
                  <td class="data">
                  <input size="10" maxlength="9" name="license" type="text" /> (erste 8 Stellen, Format XXXX-YYYY)
                  </td>
              </tr>
              <tr>
                  <td valign="top">Thema
                  </td>
                  <td class="data">
                  <select name="topic">
	<option value="0" selected="selected">Bitte ausw&auml;hlen >></option>
	<option value="100">--- SECURITY ---------------</option>
	<option value="18">Virenscanner</option>
	<option value="6">Firewall</option>
	<option value="12">Proxy</option>
	<option value="101">--- E-MAIL / GROUPWARE -----</option>
	<option value="3">Email</option>
	<option value="20">Groupware</option>
	<option value="14">Spamfilter</option>
	<option value="4">Fax</option>
	<option value="102">--- NETZWERK ---------------</option>
	<option value="10">LAN/Routing/DHCP</option>
	<option value="9">Internetzugang</option>
	<option value="5">Fernzugriff/RAS</option>
	<option value="19">VPN</option>
	<option value="103">--- SYSTEM -----------------</option>
	<option value="8">Installation</option>
	<option value="7">Hardware</option>
	<option value="1">Backup</option>
	<option value="16">Update</option>
	<option value="17">Weboberfl&auml;che</option>
	<option value="15">Statistik</option>
	<option value="11">Lizenz/Demo</option>
	<option value="104">--- SONSTIGES --------------</option>
	<option value="2">Clientsoftware</option>
	<option value="13">Sonstiges</option>
</select>
                  </td>
              </tr>
              <tr>
                  <td valign="top">Betreff<span class="required">*</span>
                  </td>
                  <td class="data">
                  <input size="60" maxlength="255" name="subject" type="text" />
                  </td>
              </tr>
              <tr>
                  <td valign="top">Beschreibung<span class="required">*</span>
                  </td>
                  <td class="data">
                  <textarea rows="15" cols="55" wrap="hard" name="description"></textarea>
                  </td>
              </tr>
              <tr>
                  <td valign="top">
                  </td>
                  <td class="data">
                  <input class="submitbutton" name="sub" value="Weiter" type="submit" />
                  </td>
              </tr><input name="_qf__supportform1" type="hidden" value="" />

             </table>
            </form>

<p class="smallgrey">* Pflichtfeld</p>

<!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../download/index.php">Software</a></li>
	<li><a href="../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="anfrage.php">Support-Anfrage</a></li>
	<li><a href="handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="antispam/index.html">Blacklist Performance</a></li>
	<li><a href="schulung.php">Schulung</a></li>
	<li><a href="fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../kaufen/index.php">Partner finden</a></li>
	<li><a href="../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../impressum.php">Impressum</a>
		<a href="../../en/developer/index.html">Entwickler</a>
		<a href="../datenschutz.php">Datenschutz</a>
		<a href="../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 4

Array
(
    [type] => 2048
    [message] => Non-static method PEAR::isError() should not be called statically, assuming $this from incompatible context
    [file] => /usr/share/pear/HTML/QuickForm.php
    [line] => 634
)
 -->

<!-- footer end -->

</body>
</html>
