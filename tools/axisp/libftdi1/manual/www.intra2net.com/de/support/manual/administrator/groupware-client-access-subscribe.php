<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Fremde Ordner verbinden | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client-access.php" title="21. Kapitel - Freigaben und Zugriff auf fremde Ordner"><link rel="prev" href="groupware-client-access.php" title="21. Kapitel - Freigaben und Zugriff auf fremde Ordner"><link rel="next" href="ch21s03.php" title="21.3. Mehrere Serverkonten">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="groupware-client-access-subscribe.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-access-subscribe.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">21.2. Fremde Ordner verbinden</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-access.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">21. Kapitel - Freigaben und Zugriff auf fremde Ordner</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="ch21s03.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-access-subscribe"></a>21.2. Fremde Ordner verbinden</h2></div></div></div><a class="indexterm" name="groupware-client-access-subscribe1"></a><a class="indexterm" name="groupware-client-access-subscribe2"></a><a class="indexterm" name="groupware-client-access-subscribe3"></a><p>Gehen Sie wie folgt vor, um Ordner zu verbinden, die Ihnen andere Benutzer freigegeben
            haben:</p><div class="procedure"><ol type="1"><li><p>Kl&auml;ren Sie zuerst, ob es sich um einen Ordner mit E-Mails oder mit
                    Groupware-Daten handelt. Das Abonnieren von Ordnern mit E-Mails als Inhalt ist
                    in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-account-email.php#groupware-client-account-email-subscription">Abschnitt&nbsp;20.2.2, &#8222;Abonnieren von Ordnern&#8220;</a> beschrieben.
                    Handelt es sich um einen Ordner mit Groupware-Daten, fahren Sie hier
                    fort.</p></li><li><p>&Ouml;ffnen Sie das Men&uuml; <span class="guimenu">Groupware Client&nbsp;&gt;&nbsp;Ordner
                        verbinden</span>.</p></li><li><p>Auf der rechten Seite (Server-Konten) erscheinen die Ihnen freigegebenen
                    Ordner unterhalb von <span class="guilabel">&raquo;Andere Benutzer</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/access-subscribe03.png"></div></div></li><li><p>Klicken Sie den gew&uuml;nschten Ordner auf der rechten Seite an und halten Sie die
                    Maustaste gedr&uuml;ckt. Ziehen Sie den Ordner dann mit gedr&uuml;ckter Maustaste auf den
                    Ordner <span class="guilabel">&raquo;Andere Benutzer</span> auf der linken Seite
                    (Outlook). Lassen Sie dort die Maustaste los.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/access-subscribe04.png"></div></div><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/access-subscribe05.png"></div></div></li><li><p>Sie werden nun gefragt, was f&uuml;r eine Art von Verbindung Sie erstellen m&ouml;chten.
                    Eine Verbindung vom Typ <span class="guilabel">Einfach</span> verbindet nur den einen
                    gew&auml;hlten Ordner. Eine Verbindung vom Typ <span class="guilabel">Baum</span> verbindet
                    den gew&auml;hlten Ordner und alle seine freigegebenen Unterordner.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/access-subscribe06.png"></div></div></li><li><p>Der verbundene Ordner erscheint nun unterhalb von <span class="guilabel">&raquo;Andere
                        Benutzer</span> und dem Benutzernamen auf der linken Seite
                    (Outlook).</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/access-subscribe07.png"></div></div></li></ol></div><a class="indexterm" name="d0e7360"></a><a class="indexterm" name="d0e7361"></a><a class="indexterm" name="d0e7362"></a></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-access.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client-access.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="ch21s03.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">21. Kapitel - Freigaben und Zugriff auf fremde Ordner&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;21.3. Mehrere Serverkonten</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
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

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>